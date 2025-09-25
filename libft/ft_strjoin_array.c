/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchabeau <cchabeau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:08:46 by cchabeau          #+#    #+#             */
/*   Updated: 2023/05/19 13:39:31 by cchabeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strjoin_arr(char *s1, char **arr, int size)
{
	int		i;
	int		j;
	char	**new_arr;

	if (!s1 || !arr)
		return (NULL);
	new_arr = malloc(sizeof(char *) * (size + 2));
	if (!new_arr)
		return (NULL);
	i = -1;
	j = 0;
	new_arr[j] = ft_strdup(s1);
	if (!new_arr[j])
		return (NULL);
	j++;
	while (arr[++i])
	{
		new_arr[j] = ft_strdup(arr[i]);
		if (!new_arr[j])
			return (NULL);
		j++;
	}
	new_arr[j] = NULL;
	return (new_arr);
}
