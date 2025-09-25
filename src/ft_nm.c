
#include "../includes/ft_nm.h"

void nm(char *ptr, int arch_type, char *filename, t_arg *arg)
{
	if (arch_type == FILE_TOO_SHORT)
	{
		ft_printf("bfd plugin: %s: file too short\n", filename);
		ft_printf("nm: %s: file format not recognized\n", filename);
		return;
	}
	else if (arch_type == ELFCLASS64)
		handle_elf64(ptr, filename, arg);
	else if (arch_type == ELFCLASS32)
		handle_elf32(ptr, filename, arg);
	else
	{
		ft_printf("nm: %s: file format not recognized\n", filename);
		return;
	}
}
