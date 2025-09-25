/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchabeau <cchabeau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:44:17 by cchabeau          #+#    #+#             */
/*   Updated: 2022/10/22 18:09:59 by cchabeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = -1;
	while (src[++i] != '\0' && dstsize > 1)
	{
		dst[i] = src[i];
		dstsize--;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (len);
}
