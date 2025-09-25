/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchabeau <cchabeau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:52:19 by cchabeau          #+#    #+#             */
/*   Updated: 2023/05/25 17:28:06 by cchabeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (str - len);
}

char	*ft_strjoin_s1(char *s1, char *s2)
{
	size_t	len;
	size_t	len_s1;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len = len_s1 + ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	free(s1 - len_s1);
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (str - len);
}

char	*ft_strjoin_s2(char *s1, char *s2)
{
	size_t	len;
	size_t	len_s2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len_s2 = ft_strlen(s2);
	len = ft_strlen(s1) + len_s2;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	free(s2 - len_s2);
	*str = '\0';
	return (str - len);
}

char	*ft_strjoin_all(char *s1, char *s2)
{
	size_t	len;
	size_t	len_s1;
	size_t	len_s2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len = len_s1 + len_s2;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (*s1)
		*str++ = *s1++;
	free(s1 - len_s1);
	while (*s2)
		*str++ = *s2++;
	free(s2 - len_s2);
	*str = '\0';
	return (str - len);
}
