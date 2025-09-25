
#include "../includes/ft_nm.h"

/*
*	Get ELF Header from file and return ELF CLASS
*
*	Return value:
*			0 => Invalid Class
*			1 => 32Bit Class
*			2 => 64Bit Class
*
*/

int detect_arch(char *ptr, size_t size)
{
	unsigned char *ident = (unsigned char *)ptr;

	if (size < EI_NIDENT)
		return (FILE_TOO_SHORT);

	if (ident[EI_MAG0] != ELFMAG0 || ident[EI_MAG1] != ELFMAG1 || 
		ident[EI_MAG2] != ELFMAG2 || ident[EI_MAG3] != ELFMAG3)
	{
		return (ELFCLASSNONE);
	}
	
	if (ident[EI_CLASS] != ELFCLASS32 && ident[EI_CLASS] != ELFCLASS64)
		return (ELFCLASSNONE);

	if (ident[EI_DATA] != ELFDATA2LSB && ident[EI_DATA] != ELFDATA2MSB)
		return (ELFCLASSNONE);

	if (ident[EI_VERSION] != EV_CURRENT)
		return (ELFCLASSNONE);

	if (ident[EI_CLASS] == ELFCLASS32)
	{
		if (size < sizeof(Elf32_Ehdr))
			return (FILE_TOO_SHORT);

		if (ident[EI_DATA] == ELFDATA2MSB)
			return (ELFCLASS32);

		Elf32_Ehdr *ehdr = (Elf32_Ehdr *)ptr;
		
		if (ehdr->e_ehsize != sizeof(Elf32_Ehdr))
			return (ELFCLASSNONE);

		if (ehdr->e_shoff > 0 && ehdr->e_shoff >= size)
			return (FILE_TOO_SHORT);

		if (ehdr->e_shnum > 0)
		{
			if (ehdr->e_shentsize != sizeof(Elf32_Shdr))
				return (ELFCLASSNONE);
			
			if (ehdr->e_shstrndx >= ehdr->e_shnum && ehdr->e_shstrndx != SHN_XINDEX)
				return (ELFCLASSNONE);
			
			size_t sections_size = ehdr->e_shnum * ehdr->e_shentsize;
			if (ehdr->e_shoff + sections_size > size)
				return (FILE_TOO_SHORT);
		}

		if (ehdr->e_phnum > 0)
		{
			if (ehdr->e_phentsize != sizeof(Elf32_Phdr))
				return (ELFCLASSNONE);
			
			if (ehdr->e_phoff >= size)
				return (FILE_TOO_SHORT);
			
			size_t pheaders_size = ehdr->e_phnum * ehdr->e_phentsize;
			if (ehdr->e_phoff + pheaders_size > size)
				return (FILE_TOO_SHORT);
		}
	}
	else if (ident[EI_CLASS] == ELFCLASS64)
	{
		if (size < sizeof(Elf64_Ehdr))
			return (FILE_TOO_SHORT);

		if (ident[EI_DATA] == ELFDATA2MSB)
			return (ELFCLASS64);

		Elf64_Ehdr *ehdr = (Elf64_Ehdr *)ptr;
		
		if (ehdr->e_ehsize != sizeof(Elf64_Ehdr))
			return (ELFCLASSNONE);

		if (ehdr->e_shoff > 0 && ehdr->e_shoff >= size)
			return (FILE_TOO_SHORT);

		if (ehdr->e_shnum > 0)
		{
			if (ehdr->e_shentsize != sizeof(Elf64_Shdr))
				return (ELFCLASSNONE);
			
			if (ehdr->e_shstrndx >= ehdr->e_shnum && ehdr->e_shstrndx != SHN_XINDEX)
				return (ELFCLASSNONE);
			
			size_t sections_size = ehdr->e_shnum * ehdr->e_shentsize;
			if (ehdr->e_shoff + sections_size > size)
				return (FILE_TOO_SHORT);
		}

		if (ehdr->e_phnum > 0)
		{
			if (ehdr->e_phentsize != sizeof(Elf64_Phdr))
				return (ELFCLASSNONE);
			
			if (ehdr->e_phoff >= size)
				return (FILE_TOO_SHORT);
			
			size_t pheaders_size = ehdr->e_phnum * ehdr->e_phentsize;
			if (ehdr->e_phoff + pheaders_size > size)
				return (FILE_TOO_SHORT);
		}
	}
		
	return (ident[EI_CLASS]);
}