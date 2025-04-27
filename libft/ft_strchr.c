/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:32:47 by syukna            #+#    #+#             */
/*   Updated: 2024/11/25 16:40:41 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)str;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == (char)c)
			return ((char *)&ptr[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&ptr[i]);
	return (0);
}
