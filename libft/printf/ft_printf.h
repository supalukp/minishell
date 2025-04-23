/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:33:25 by spunyapr          #+#    #+#             */
/*   Updated: 2024/12/06 13:45:52 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
int		ft_printf(const char *format, ...);
size_t	ft_printchar(int c);
size_t	ft_printstr(char const *str);
size_t	ft_printnbr(int n);
size_t	ft_print_unsigned_nbr(unsigned int n);
size_t	ft_convert_base(unsigned int n, char *base, int alpha);
size_t	ft_convert_pointer(unsigned long n, char *base, int alpha);
size_t	ft_print_ptr(void *ptr);
char	find_percent(const char *format, int index);
size_t	call_function(const char *format, int index, va_list ptr, char percent);

#endif