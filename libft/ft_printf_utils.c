/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchabeau <cchabeau@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:23:46 by cchabeau          #+#    #+#             */
/*   Updated: 2023/02/24 20:03:48 by cchabeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_str(char *str)
{
	int	len;

	if (!str)
		return (write(1, "(null)", 6));
	len = ft_strlen(str);
	return (write(1, str, len));
}

static size_t	ft_print_nbr(long int n)
{
	size_t	sign;
	size_t	len;

	sign = 1;
	len = 0;
	if (n < 0)
	{
		len += ft_print_char('-');
		sign = -1;
	}
	n *= sign;
	if (n < 10)
		len += ft_print_char(n + 48);
	else
	{
		len += ft_print_nbr(n / 10);
		len += ft_print_nbr(n % 10);
	}
	return (len);
}

static size_t	ft_print_nbr_base(unsigned long int n, const char *base)
{
	size_t	base_len;
	size_t	len;

	if (!base || ft_strlen(base) < 2)
		return (0);
	base_len = ft_strlen(base);
	len = 0;
	if (n < base_len)
		len += ft_print_char(base[n]);
	else
	{
		len += ft_print_nbr_base(n / base_len, base);
		len += ft_print_nbr_base(n % base_len, base);
	}
	return (len);
}

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

size_t	ft_convert(char type, va_list ap)
{
	int	len;

	len = 0;
	if (type == 'c')
		len += ft_print_char(va_arg(ap, int));
	if (type == 's')
		len += ft_print_str(va_arg(ap, char *));
	if (type == 'p')
	{
		len += ft_print_str("0x")
			+ ft_print_nbr_base(va_arg(ap, unsigned long), "0123456789abcdef");
	}
	if (type == 'd' || type == 'i')
		len += ft_print_nbr(va_arg(ap, int));
	if (type == 'u')
		len += ft_print_nbr_base(va_arg(ap, unsigned), "0123456789");
	if (type == 'x')
		len += ft_print_nbr_base(va_arg(ap, unsigned), "0123456789abcdef");
	if (type == 'X')
		len += ft_print_nbr_base(va_arg(ap, unsigned), "0123456789ABCDEF");
	if (type == '%')
		len += ft_print_char('%');
	return (len);
}
