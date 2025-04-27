/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:44:12 by syukna            #+#    #+#             */
/*   Updated: 2025/01/23 13:46:53 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	handle_long_neg(int fd)
{
	ft_putstr_fd("-2147483648", fd);
	return (11);
}

int	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		count;

	count = 0;
	if (n == -2147483648)
		count += handle_long_neg(fd);
	else
	{
		if (n < 0)
		{
			count += ft_putchar_fd('-', fd);
			count += ft_putnbr_fd(n * -1, fd);
		}
		if (n >= 0 && n <= 9)
		{
			c = n + 48;
			count += ft_putchar_fd(c, fd);
		}
		if (n >= 10)
		{
			count += ft_putnbr_fd(n / 10, fd);
			count += ft_putnbr_fd(n % 10, fd);
		}
	}
	return (count);
}
