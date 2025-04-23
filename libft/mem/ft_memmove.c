/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:42:07 by spunyapr          #+#    #+#             */
/*   Updated: 2025/02/11 13:06:51 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*c_dest;
	unsigned const char	*c_src;
	size_t				i;

	c_dest = (unsigned char *)dest;
	c_src = (unsigned const char *)src;
	i = 0;
	if (!c_dest && !c_src)
		return (NULL);
	if (c_dest > c_src)
	{
		i = n;
		while (i > 0)
		{
			c_dest[i - 1] = c_src[i - 1];
			i--;
		}
		return (dest);
	}
	while (i < n)
	{
		c_dest[i] = c_src[i];
		i++;
	}
	return (dest);
}
