/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:43:22 by syukna            #+#    #+#             */
/*   Updated: 2024/11/25 20:10:39 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*rtn;

	if (nitems != 0 && (SIZE_MAX / nitems) < size)
		return (NULL);
	rtn = malloc(nitems * size);
	if (!rtn)
		return (NULL);
	ft_bzero(rtn, nitems * size);
	return (rtn);
}
