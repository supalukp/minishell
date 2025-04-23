/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:49:20 by spunyapr          #+#    #+#             */
/*   Updated: 2025/02/11 13:06:46 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned const char	*p;
	unsigned const char	*t;

	i = 0;
	p = s1;
	t = s2;
	if (n == 0)
		return (0);
	while (p[i] == t[i] && i < (n - 1))
	{
		i++;
	}
	return ((unsigned char)p[i] - (unsigned char)t[i]);
}
