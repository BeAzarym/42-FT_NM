
#include "../includes/ft_nm.h"

static void process_file(char *filename, t_arg *arg)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		return;
	}

	struct stat buffer;
	if (fstat(fd, &buffer) < 0)
	{
		perror("fstat");
		close(fd);
		return;
	}

	if (buffer.st_size == 0)
	{
		close(fd);
		return;
	}

	if (buffer.st_size < EI_NIDENT)
	{
		ft_printf("bfd plugin: %s: file too short\n", filename);
		close(fd);
		return;
	}

	char *ptr = mmap(0, buffer.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr == MAP_FAILED)
	{
		ft_printf("bfd plugin: %s: file too short\n", filename);
		close(fd);
		return;
	}

	t_arg default_arg = {NULL, 0, 0, 0, 0, 0, 0 , -1};
	if (!arg)
		arg = &default_arg;

	nm(ptr, detect_arch(ptr, buffer.st_size), filename, arg);

	if (munmap(ptr, buffer.st_size) < 0)
	{
		perror("munmap");
	}
	close(fd);
}

int main(int argc, char **argv)
{
	t_arg arg;

	arg = handle_flag(argc, argv, arg);

	if (!arg.file_count && !arg.filenames && arg.a == 0 && arg.g == 0 && arg.r == 0 && arg.u == 0 && arg.p == 0)
	{
		ft_printf("nm: option invalide -- '%c'\n", arg.flag);
		return (1);
	}
	if (arg.file_count == 0)
	{
		process_file("a.out", &arg);
	}
	else
	{
		for (int i = 0; i < arg.file_count; i++)
		{
			process_file(arg.filenames[i], &arg);
		}
	}

	if (arg.filenames)
		free(arg.filenames);

	return (0);
}
