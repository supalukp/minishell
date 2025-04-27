/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:19:11 by syukna            #+#    #+#             */
/*   Updated: 2025/01/23 13:47:41 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../libft.h"
#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>

static int	includedchar(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

int	handle_str(char *str)
{
	int		count;

	count = 0;
	if (str == NULL)
		count += ft_putstr_fd("(null)", 1);
	else
		count += ft_putstr_fd(str, 1);
	return (count);
}

int	send_function(char c, va_list args)
{
	int		count;

	count = 0;
	if (c == 'c')
		count += ft_putchar_fd(va_arg(args, int), 1);
	else if (c == '%')
		count += ft_putchar_fd('%', 1);
	else if (c == 's')
		count += handle_str(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		count += ft_putnbr_fd(va_arg(args, int), 1);
	else if (c == 'u')
		count += ft_print_uns(va_arg(args, unsigned int), 1);
	else if (c == 'x')
		count += ft_print_hex(va_arg(args, unsigned int), 0);
	else if (c == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), 1);
	else if (c == 'p')
		count += ft_print_p(va_arg(args, void *));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	ptr;

	i = 0;
	count = 0;
	va_start(ptr, format);
	if (format == NULL)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!format[i])
				return (-1);
			else if (format[i] && includedchar(format[i], "cspdiuxX%"))
				count += send_function(format[i], ptr);
		}
		else if (format[i] != '%')
			count += ft_putchar_fd(format[i], 1);
		i++;
	}
	va_end(ptr);
	return (count);
}
