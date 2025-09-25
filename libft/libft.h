/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchabeau <cchabeau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:10:00 by cchabeau          #+#    #+#             */
/*   Updated: 2025/09/22 15:50:42 by cchabeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 500
#endif
#if BUFFER_SIZE > 99999 || BUFFER_SIZE < 1
#undef BUFFER_SIZE
#define BUFFER_SIZE 500
#endif

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

size_t ft_strlen(const char *s);
int ft_islower(int c);
int ft_isupper(int c);
int ft_isalpha(int c);
int ft_isdigit(int c);
int ft_isalnum(int c);
int ft_isascii(int c);
int ft_isprint(int c);
void *ft_memset(void *b, int c, size_t len);
void ft_bzero(void *s, size_t n);
void *ft_memcpy(void *dst, const void *src, size_t n);
void *ft_memmove(void *dst, const void *src, size_t len);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t ft_strlcat(char *dst, const char *src, size_t dstsize);
int ft_toupper(int c);
int ft_tolower(int c);
int ft_memcmp(const void *s1, const void *s2, size_t n);
int ft_strncmp(const char *s1, const char *s2, size_t n);
void *ft_memchr(const void *s, int c, size_t n);
char *ft_strchr(const char *s, int c);
char *ft_strrchr(const char *s, int c);
char *ft_strnstr(const char *haystack, const char *needle,
				 size_t len);
int ft_atoi(const char *str);
void *ft_calloc(size_t count, size_t size);
char *ft_strdup(const char *s);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strtrim(char const *s1, char const *set);
char **ft_split(char const *s, char c);
char *ft_itoa(int n);
char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
void ft_striteri(char *s, void (*f)(unsigned int, char *));
void ft_putchar_fd(char c, int fd);
void ft_putstr_fd(char *s, int fd);
void ft_putendl_fd(char *s, int fd);
void ft_putnbr_fd(int n, int fd);
t_list *ft_lstnew(void *content);
void ft_lstadd_front(t_list **lst, t_list *new);
void ft_lstadd_back(t_list **lst, t_list *new);
void ft_lstdelone(t_list *lst, void (*del)(void *));
void ft_lstclear(t_list **lst, void (*del)(void *));
int ft_lstsize(t_list *lst);
t_list *ft_lstlast(t_list *lst);
void ft_lstiter(t_list *lst, void (*f)(void *));
t_list *ft_lstmap(t_list *lst, void *(*f)(void *),
				  void (*del)(void *));
size_t ft_convert(char type, va_list ap);
int ft_print_char(char c);
int ft_printf(const char *format, ...);
char *get_next_line(int fd);
void ft_array_print(char **array);
char **ft_array_dup(char **array);
void ft_array_clear(char **array);
char **ft_array_join(char **s1, char **s2);
char **ft_array_join_s1(char **s1, char **s2);
char **ft_array_join_s2(char **s1, char **s2);
char **ft_array_join_all(char **s1, char **s2);
char **ft_strjoin_arr(char *s1, char **arr, int size);
int ft_arraylen(char **arr);
int ft_strcmp(const char *s1, const char *s2);

#endif