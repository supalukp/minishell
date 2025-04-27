/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:18:43 by syukna            #+#    #+#             */
/*   Updated: 2025/01/23 13:47:40 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"
#include <stdint.h>

static int	ft_print_ptr(unsigned long long n)
{
	int	count;

	count = 0;
	if (n < 16)
		count += ft_char_to_hex(n, 0);
	else if (n >= 16)
	{
		count += ft_print_ptr(n / 16);
		count += ft_print_ptr(n % 16);
	}
	return (count);
}

int	ft_print_p(void *ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
		count += ft_putstr_fd("(nil)", 1);
	else
	{
		count += ft_putstr_fd("0x", 1);
		count += ft_print_ptr((unsigned long long)ptr);
	}
	return (count);
}
