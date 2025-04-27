/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:41:30 by syukna            #+#    #+#             */
/*   Updated: 2024/11/25 19:00:29 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rtn;
	size_t	mallen;
	size_t	slen;

	slen = (size_t)ft_strlen(s);
	if (start >= (unsigned int)ft_strlen(s) || !s)
	{
		rtn = ft_calloc(1, sizeof(char));
		if (!rtn)
			return (NULL);
		rtn[0] = '\0';
		return (rtn);
	}
	if (slen >= (slen - ((size_t)start + len)))
		mallen = len;
	else
		mallen = ft_strlen(s) - start;
	rtn = ft_calloc(mallen + 1, sizeof(char));
	if (!rtn)
		return (NULL);
	ft_strlcpy(rtn, &s[start], mallen + 1);
	return (rtn);
}
