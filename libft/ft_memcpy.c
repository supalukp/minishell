/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:33:57 by syukna            #+#    #+#             */
/*   Updated: 2024/11/23 17:10:54 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *str, size_t n)
{
	size_t			i;
	unsigned char	*ptr_dest;
	unsigned char	*ptr_str;

	i = 0;
	ptr_dest = (unsigned char *)dest;
	ptr_str = (unsigned char *)str;
	if (ptr_str == 0 && ptr_dest == 0)
		return (NULL);
	while (i < n)
	{
		ptr_dest[i] = ptr_str[i];
		i++;
	}
	return (dest);
}
