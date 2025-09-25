
#include "../includes/ft_nm.h"

static t_arg init_struct(t_arg arg)
{
	arg.filenames = NULL;
	arg.file_count = 0;
	arg.a = 0;
	arg.g = 0;
	arg.p = 0;
	arg.r = 0;
	arg.u = 0;

	return (arg);
}

static int is_valid_flag_char(char c)
{
	return (c == 'a' || c == 'g' || c == 'r' || c == 'u' || c == 'p');
}

static int is_flag_argument(char *arg)
{
	if (arg[0] != '-' || arg[1] == '\0')
		return (0);
	
	for (int i = 1; arg[i]; i++)
	{
		if (!is_valid_flag_char(arg[i]))
			return (arg[i]);
	}
	return (1);
}

t_arg handle_flag(int argc, char **argv, t_arg arg_struct)
{
	arg_struct = init_struct(arg_struct);
	
	for (int i = 1; i < argc; i++)
	{
		if ((arg_struct.flag = is_flag_argument(argv[i])) > 1)
		{
			return arg_struct;
		}	

		if (is_flag_argument(argv[i]) == 0)
			arg_struct.file_count++;
	}
	
	if (arg_struct.file_count > 0)
	{
		arg_struct.filenames = malloc(sizeof(char*) * arg_struct.file_count);
		if (!arg_struct.filenames)
			return (arg_struct);
	}
	
	int file_index = 0;
	for (int i = 1; i < argc; i++)
	{
		if (is_flag_argument(argv[i]))
		{
			for (size_t j = 1; j < ft_strlen(argv[i]); j++)
			{
				switch (argv[i][j])
				{
				case 'a':
					arg_struct.a = 1;
					break;
				case 'g':
					arg_struct.g = 1;
					break;
				case 'r':
					arg_struct.r = 1;
					break;
				case 'u':
					arg_struct.u = 1;
					break;
				case 'p':
					arg_struct.p = 1;
					break;
				}
			}
		}
		else
		{
			arg_struct.filenames[file_index++] = argv[i];
		}
	}
	
	return (arg_struct);
}
