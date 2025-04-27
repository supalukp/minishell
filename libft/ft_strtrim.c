/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:10:40 by syukna            #+#    #+#             */
/*   Updated: 2024/11/25 18:59:01 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	includedchar(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(set))
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	countchar(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (includedchar(s1[i], set))
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;
	int		len;

	if (!s1 || !set)
		return (NULL);
	start = countchar(s1, set);
	end = ft_strlen(s1) - 1;
	while (end >= start && includedchar(s1[end], set))
		end--;
	if (start > end)
	{
		str = ft_calloc(1, sizeof(char));
		if (!str)
			return (NULL);
		return (str);
	}
	len = end - start + 1;
	str = ft_calloc(len + 1, 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[start], len + 1);
	return (str);
}
