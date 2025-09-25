
#include "../includes/ft_nm.h"

static void print_symbol_64(Elf64_Sym *sym, char *name, Elf64_Shdr *shdr, Elf64_Ehdr *ehdr);
static char get_symbol_type_64(Elf64_Sym *symbol, Elf64_Shdr *section_header, Elf64_Ehdr *elf_header);
static char *normalize_hex_address(Elf64_Addr address);
static void sort_symbols(t_symbol_map64 *symbols, int count);
static void sort_symbols_reverse(t_symbol_map64 *symbols, int count);
static int should_display_symbol(Elf64_Sym *sym, t_arg *arg);
static int find_symbol_and_str_sections(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, char *shstrtab, Elf64_Shdr **out_sym, Elf64_Shdr **out_str);

void handle_elf64(char *ptr, char *filename, t_arg *arg)
{
	Elf64_Ehdr *elf_header = (Elf64_Ehdr *)ptr;
	unsigned char *ident = (unsigned char *)ptr;

	if (!elf_header)
	{
		ft_printf("nm: %s: file format not recognized\n", filename);
		return;
	}

	if (ident[EI_DATA] == ELFDATA2MSB)
	{
		ft_printf("nm: %s: aucun symbole\n", filename);
		return;
	}

	if (elf_header->e_version != EV_CURRENT)
	{
		ft_printf("nm: %s: aucun symbole\n", filename);
		return;
	}

	if (elf_header->e_shoff == 0 || elf_header->e_shnum == 0)
	{
		ft_printf("nm: %s: file format not recognized\n", filename);
		return;
	}

	if (elf_header->e_machine != EM_X86_64 && elf_header->e_machine != EM_386)
	{
		ft_printf("nm: %s: aucun symbole\n", filename);
		return;
	}

	Elf64_Shdr *section_header = (Elf64_Shdr *)(ptr + elf_header->e_shoff);
	Elf64_Shdr *section_name = &section_header[elf_header->e_shstrndx];
	char *section_data = ptr + section_name->sh_offset;

	Elf64_Shdr *symbols_table = NULL;
	Elf64_Shdr *str_table = NULL;

	if (find_symbol_and_str_sections(elf_header, section_header, section_data, &symbols_table, &str_table) < 0)
	{
		ft_printf("nm: %s: aucun symbole\n", filename);
		return;
	}

	Elf64_Sym *symbols = (Elf64_Sym *)(ptr + symbols_table->sh_offset);
	char *string_table = ptr + str_table->sh_offset;

	int num_symbols = (symbols_table->sh_entsize != 0)
						  ? (int)(symbols_table->sh_size / symbols_table->sh_entsize)
						  : (int)(symbols_table->sh_size / sizeof(Elf64_Sym));

	t_symbol_map64 *valid_symbols = malloc(num_symbols * sizeof(t_symbol_map64));
	int valid_count = 0;

	for (int i = 0; i < num_symbols; i++)
	{
		Elf64_Sym *sym = &symbols[i];
		char *symbol_name = string_table + sym->st_name;

		if (sym->st_name == 0 || symbol_name[0] == '\0')
			continue;

		if (!should_display_symbol(sym, arg))
			continue;

		valid_symbols[valid_count].sym = sym;
		valid_symbols[valid_count].name = symbol_name;
		valid_count++;
	}

	if (!arg->p)
	{
		if (arg->r)
			sort_symbols_reverse(valid_symbols, valid_count);
		else
			sort_symbols(valid_symbols, valid_count);
	}

	for (int i = 0; i < valid_count; i++)
	{
		print_symbol_64(valid_symbols[i].sym, valid_symbols[i].name, section_header, elf_header);
	}

	free(valid_symbols);
}

char *normalize_hex_address(Elf64_Addr address)
{
	static char buffer[17];
	char hex_str[17];
	int len, i;

	if (address == 0)
	{
		ft_memset(buffer, '0', 16);
		buffer[16] = '\0';
		return buffer;
	}

	i = 0;
	Elf64_Addr temp = address;
	while (temp > 0 && i < 16)
	{
		int digit = temp % 16;
		if (digit < 10)
			hex_str[i] = '0' + digit;
		else
			hex_str[i] = 'a' + (digit - 10);
		temp /= 16;
		i++;
	}
	hex_str[i] = '\0';
	len = i;

	for (int j = 0; j < len / 2; j++)
	{
		char c = hex_str[j];
		hex_str[j] = hex_str[len - 1 - j];
		hex_str[len - 1 - j] = c;
	}

	ft_memset(buffer, '0', 16);
	buffer[16] = '\0';

	ft_strlcpy(buffer + (16 - len), hex_str, len + 1);

	return buffer;
}

void print_symbol_64(Elf64_Sym *symbol, char *symbol_name, Elf64_Shdr *section_header, Elf64_Ehdr *elf_header)
{
	char type = get_symbol_type_64(symbol, section_header, elf_header);

	if ((type == 'w' || type == 'v') || type == 'U')
	{
		ft_printf("                 %c %s\n", type, symbol_name);
	}
	else
	{
		ft_printf("%s %c %s\n", normalize_hex_address(symbol->st_value), type, symbol_name);
	}
}

char get_symbol_type_64(Elf64_Sym *symbol, Elf64_Shdr *section_header, Elf64_Ehdr *elf_header)
{
	if (ELF64_ST_BIND(symbol->st_info) == STB_WEAK)
	{
		if (ELF64_ST_TYPE(symbol->st_info) == STT_OBJECT)
			return ((symbol->st_shndx == SHN_UNDEF) ? 'v' : 'V');
		else
		{
			return ((symbol->st_shndx == SHN_UNDEF) ? 'w' : 'W');
		}
	}

	if (symbol->st_shndx == SHN_UNDEF)
		return ('U');
	if (symbol->st_shndx == SHN_ABS)
		return ((ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL) ? 'A' : 'a');
	if (symbol->st_shndx == SHN_COMMON)
		return ('C');

	if (symbol->st_shndx < elf_header->e_shnum)
	{
		Elf64_Shdr *section = &section_header[symbol->st_shndx];

		if (section->sh_type == SHT_NOBITS)
			return ((ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL) ? 'B' : 'b');

		if (section->sh_flags & SHF_EXECINSTR)
			return ((ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL) ? 'T' : 't');

		if (section->sh_flags & SHF_WRITE)
			return ((ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL) ? 'D' : 'd');
		return ((ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL) ? 'R' : 'r');
	}
	return ('?');
}

static void sort_symbols(t_symbol_map64 *symbols, int count)
{
	int i, j;
	t_symbol_map64 tmp;

	for (i = 0; i < count - 1; i++)
	{
		for (j = 0; j < count - i - 1; j++)
		{
			if (compare_nm_style(symbols[j].name, symbols[j + 1].name) > 0)
			{
				tmp = symbols[j];
				symbols[j] = symbols[j + 1];
				symbols[j + 1] = tmp;
			}
		}
	}
}

static int find_symbol_and_str_sections(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, char *shstrtab, Elf64_Shdr **out_sym, Elf64_Shdr **out_str)
{
	Elf64_Shdr *sym = NULL;
	Elf64_Shdr *str = NULL;

	for (int i = 0; i < ehdr->e_shnum; ++i)
	{
		char *name = shstrtab + shdr[i].sh_name;
		if (!sym && ft_strcmp(name, ".symtab") == 0)
			sym = &shdr[i];
		if (!str && ft_strcmp(name, ".strtab") == 0)
			str = &shdr[i];
		if (sym && str)
			break;
	}

	if (!sym || !str)
		return -1;

	*out_sym = sym;
	*out_str = str;
	return 0;
}

static void sort_symbols_reverse(t_symbol_map64 *symbols, int count)
{
	int i, j;
	t_symbol_map64 tmp;

	for (i = 0; i < count - 1; i++)
	{
		for (j = 0; j < count - i - 1; j++)
		{
			if (compare_nm_style(symbols[j].name, symbols[j + 1].name) < 0)
			{
				tmp = symbols[j];
				symbols[j] = symbols[j + 1];
				symbols[j + 1] = tmp;
			}
		}
	}
}
static int should_display_symbol(Elf64_Sym *sym, t_arg *arg)
{
	int st_type = ELF64_ST_TYPE(sym->st_info);
	int st_bind = ELF64_ST_BIND(sym->st_info);
	int st_shndx = sym->st_shndx;
	
	if (arg->a)
	{
		return 1;
	}
	else
	{
		if (st_type == STT_FILE || st_type == STT_SECTION)
			return 0;
	}
	
	if (arg->g)
	{
		if (st_bind != STB_GLOBAL && st_bind != STB_WEAK)
			return 0;
	}
	
	if (arg->u)
	{
		if (st_shndx != SHN_UNDEF)
			return 0;
	}
	
	return 1;
}
