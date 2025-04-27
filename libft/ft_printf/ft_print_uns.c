/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uns.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:18:54 by syukna            #+#    #+#             */
/*   Updated: 2024/12/12 14:07:41 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_uns(unsigned int n, int fd)
{
	int	count;

	count = 0;
	if (n >= 0 && n <= 9)
		count += ft_putchar_fd(n + 48, fd);
	if (n >= 10)
	{
		count += ft_print_uns(n / 10, fd);
		count += ft_print_uns(n % 10, fd);
	}
	return (count);
}
