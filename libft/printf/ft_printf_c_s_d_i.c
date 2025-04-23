/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c_s_d_i.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:37:02 by spunyapr          #+#    #+#             */
/*   Updated: 2024/12/06 13:52:55 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_printchar(int c)
{
	if (write(1, &c, 1) != 1)
		return (-1);
	return (1);
}

size_t	ft_printstr(char const *str)
{
	size_t	i;
	size_t	count;

	if (!str)
		return (write(1, "(null)", 6));
	i = 0;
	count = 0;
	while (str[i])
	{
		count += ft_printchar(str[i]);
		i++;
	}
	return (count);
}

size_t	ft_printnbr(int n)
{
	size_t	len;

	len = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		len += ft_printchar('-');
		n *= -1;
	}
	if (n < 10)
		len += ft_printchar(n + 48);
	else if (n > 9)
	{
		len += ft_printnbr(n / 10);
		len += ft_printchar(n % 10 + 48);
	}
	return (len);
}
