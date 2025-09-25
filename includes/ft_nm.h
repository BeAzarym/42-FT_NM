/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchabeau <cchabeau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:44:57 by cchabeau          #+#    #+#             */
/*   Updated: 2025/09/25 20:25:00 by cchabeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
#define FT_NM_H

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "elf.h"
#include "../libft/libft.h"

#define FILE_TOO_SHORT -1

typedef struct s_arg{
	char **filenames;
	int file_count;
	int a;
	int g;
	int r;
	int u;
	int p;
	char flag;
} t_arg;

typedef struct s_symbol_map64
{
	Elf64_Sym *sym;
	char *name;
} t_symbol_map64;

typedef struct s_symbol_map32
{
	Elf32_Sym *sym;
	char *name;
} t_symbol_map32;

int detect_arch(char *ptr, size_t size);
void nm(char *ptr, int arch_type, char *filename, t_arg *arg);
void handle_elf64(char *ptr, char *filename, t_arg *arg);
void handle_elf32(char *ptr, char *filename, t_arg *arg);
int compare_nm_style(const char *s1, const char *s2);
t_arg handle_flag(int argc, char **argv, t_arg arg_struct);

#endif