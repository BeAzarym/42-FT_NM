/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchabeau <cchabeau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:47:47 by cchabeau          #+#    #+#             */
/*   Updated: 2022/10/22 17:56:24 by cchabeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dlen;
	size_t	slen;

	dlen = ft_strlen (dst);
	slen = ft_strlen (src);
	if (!dst && dstsize == 0)
		return (slen);
	if (dstsize < dlen)
		return (dstsize + slen);
	i = 0;
	while (i < dstsize && dst[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0' && ((i < (dstsize - 1)) && dstsize != 0))
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (dlen + slen);
}
