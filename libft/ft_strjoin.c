/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:38:58 by syukna            #+#    #+#             */
/*   Updated: 2024/11/25 18:57:35 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rtn;
	int		length;
	int		s1len;

	s1len = ft_strlen(s1);
	length = s1len + ft_strlen(s2) + 1;
	rtn = ft_calloc(length, 1);
	if (!rtn)
		return (NULL);
	if (s1)
		ft_strlcpy(rtn, (char *)s1, s1len + 1);
	if (s1 && s2)
		ft_strlcpy(&rtn[s1len], (char *)s2, ft_strlen(s2) + 1);
	if (!s1 && s2)
		ft_strlcpy(rtn, (char *)s2, length);
	return (rtn);
}
