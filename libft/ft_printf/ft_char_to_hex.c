/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:18:16 by syukna            #+#    #+#             */
/*   Updated: 2024/12/12 14:07:37 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_char_to_hex(int c, int caps)
{
	int	count;

	count = 0;
	if (c >= 0 && c <= 9)
		count += ft_putchar_fd(c + 48, 1);
	else if (c >= 10 && c <= 16 && caps)
		count += ft_putchar_fd(c + 55, 1);
	else if (c >= 10 && c <= 16 && !caps)
		count += ft_putchar_fd(c + 87, 1);
	return (count);
}
