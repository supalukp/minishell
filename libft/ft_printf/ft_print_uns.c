/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:18:54 by syukna            #+#    #+#             */
/*   Updated: 2025/04/30 18:05:54 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_uns(unsigned int n, int fd)
{
	int	count;

	count = 0;
	if (n <= 9)
		count += ft_putchar_fd(n + 48, fd);
	if (n >= 10)
	{
		count += ft_print_uns(n / 10, fd);
		count += ft_print_uns(n % 10, fd);
	}
	return (count);
}
