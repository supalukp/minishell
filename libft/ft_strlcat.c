/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:40:41 by syukna            #+#    #+#             */
/*   Updated: 2024/11/25 18:57:49 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *str, size_t n)
{
	size_t			i;
	size_t			j;
	size_t			initlengthdest;

	j = 0;
	initlengthdest = ft_strlen(dest);
	if (n <= initlengthdest)
		return (n + ft_strlen(str));
	i = initlengthdest;
	while (str[j] && (i + j + 1) < n)
	{
		dest[i + j] = str[j];
		j++;
	}
	if (i + j < n)
		dest[i + j] = '\0';
	return (initlengthdest + ft_strlen(str));
}
