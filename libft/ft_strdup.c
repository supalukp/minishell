/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:31:13 by syukna            #+#    #+#             */
/*   Updated: 2024/11/25 18:57:37 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char	*ft_strdup(const char *src_str)
{
	char	*dup_str;

	dup_str = ft_calloc(ft_strlen(src_str) + 1, 1);
	if (!dup_str)
		return (NULL);
	ft_strlcpy(dup_str, src_str, ft_strlen(src_str) + 1);
	return (dup_str);
}
