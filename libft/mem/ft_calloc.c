/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:48:06 by spunyapr          #+#    #+#             */
/*   Updated: 2025/02/11 13:06:39 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		i;
	int		space;
	char	*result;

	i = 0;
	if (nmemb != 0 && (SIZE_MAX / nmemb) < size)
		return (NULL);
	space = nmemb * size;
	result = malloc(space);
	if (result == NULL)
		return (NULL);
	while (i < space)
	{
		result[i] = 0;
		i++;
	}
	return ((void *)result);
}
