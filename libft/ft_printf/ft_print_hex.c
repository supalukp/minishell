/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:18:29 by syukna            #+#    #+#             */
/*   Updated: 2024/12/12 14:07:38 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int	ft_print_hex(unsigned int n, int caps)
{
	int	count;

	count = 0;
	if (n < 16)
		count += ft_char_to_hex(n, caps);
	if (n >= 16)
	{
		count += ft_print_hex(n / 16, caps);
		count += ft_print_hex(n % 16, caps);
	}
	return (count);
}
