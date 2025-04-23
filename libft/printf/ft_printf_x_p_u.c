/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_p_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:33:06 by spunyapr          #+#    #+#             */
/*   Updated: 2024/12/06 13:46:34 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_print_unsigned_nbr(unsigned int n)
{
	size_t	len;

	len = 0;
	if (n < 10)
		len += ft_printchar(n + 48);
	else if (n > 9)
	{
		len += ft_printnbr(n / 10);
		len += ft_printchar(n % 10 + 48);
	}
	return (len);
}

size_t	ft_convert_base(unsigned int n, char *base, int alpha)
{
	size_t	len;

	len = 0;
	if (n < 10)
		len += ft_printchar(n + 48);
	else if (n >= 10 && n < ft_strlen(base))
		len += ft_printchar(n + alpha);
	else
	{
		len += ft_convert_base(n / ft_strlen(base), base, alpha);
		len += ft_convert_base(n % ft_strlen(base), base, alpha);
	}
	return (len);
}

size_t	ft_convert_pointer(unsigned long n, char *base, int alpha)
{
	size_t	len;

	len = 0;
	if (n < 10)
		len += ft_printchar(n + 48);
	else if (n >= 10 && n < ft_strlen(base))
		len += ft_printchar(n + alpha);
	else
	{
		len += ft_convert_pointer(n / ft_strlen(base), base, alpha);
		len += ft_convert_pointer(n % ft_strlen(base), base, alpha);
	}
	return (len);
}

size_t	ft_print_ptr(void *ptr)
{
	size_t	len;

	len = 0;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	else
	{
		len += ft_printstr("0x");
		len += ft_convert_pointer((unsigned long)ptr, "0123456789abcdef", 87);
	}
	return (len);
}
