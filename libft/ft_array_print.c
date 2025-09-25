/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchabeau <cchabeau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:59:55 by cchabeau          #+#    #+#             */
/*   Updated: 2023/05/16 23:03:00 by cchabeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_array_print(char **array)
{
	if (!array)
		return ;
	while (*array != NULL)
	{
		ft_printf("|	{%s}	|\n", *array);
		array++;
	}
}
