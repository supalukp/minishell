/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:49:14 by spunyapr          #+#    #+#             */
/*   Updated: 2025/02/11 13:06:43 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	value;
	size_t			i;

	p = (unsigned char *)s;
	value = (unsigned char)c;
	if (n == 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (p[i] == value)
			return ((void *)p + i);
		i++;
	}
	return (NULL);
}
