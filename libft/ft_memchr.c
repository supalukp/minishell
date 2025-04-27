/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:40:32 by syukna            #+#    #+#             */
/*   Updated: 2024/11/30 14:55:37 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *ptr, int ch, size_t n)
{
	size_t			i;
	unsigned char	*ptr_ptr;
	unsigned char	ptr_ch;

	i = 0;
	ptr_ptr = (unsigned char *)ptr;
	ptr_ch = (unsigned char)ch;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (ptr_ptr[i] == ptr_ch)
			return (&ptr_ptr[i]);
		i++;
	}
	return (NULL);
}
