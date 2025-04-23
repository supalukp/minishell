/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:44:58 by spunyapr          #+#    #+#             */
/*   Updated: 2025/02/06 15:07:12 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	find_percent(const char *format, int index)
{
	while (format[index])
	{
		if (format[index] == '%')
			return (format[index + 1]);
		index++;
	}
	return (0);
}

size_t	call_function(const char *format, int index, va_list ptr, char percent)
{
	size_t	len;

	len = 0;
	if (percent == 'c')
		len += ft_printchar(va_arg(ptr, int));
	else if (percent == 's')
		len += ft_printstr(va_arg(ptr, char *));
	else if (percent == 'p')
		len += ft_print_ptr(va_arg(ptr, void *));
	else if (percent == 'd' || percent == 'i')
		len += ft_printnbr(va_arg(ptr, int));
	else if (percent == 'u')
		len += ft_print_unsigned_nbr(va_arg(ptr, unsigned int));
	else if (percent == 'x')
		len += (ft_convert_base(va_arg(ptr, int), "0123456789abcdef", 87));
	else if (percent == 'X')
		len += (ft_convert_base(va_arg(ptr, int), "0123456789ABCDEF", 55));
	else if (percent == '%')
		len += ft_printchar('%');
	else
	{
		len += ft_printchar('%');
		len += ft_printchar(format[index + 1]);
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	char	percent;
	va_list	ptr;

	va_start(ptr, format);
	i = 0;
	len = 0;
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] != '%')
			len += ft_printchar(format[i]);
		else if (format[i] == '%')
		{
			percent = find_percent(format, i);
			len += call_function(format, i, ptr, percent);
			i++;
		}
		i++;
	}
	va_end(ptr);
	return (len);
}
