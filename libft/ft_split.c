/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:43:09 by syukna            #+#    #+#             */
/*   Updated: 2025/02/19 12:42:07 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	countchar(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

// Counting the length of each string
static int	getstrlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && (char)s[i] != c)
		i++;
	i++;
	return (i);
}

static void	free_rtnlist(char **rtnlist)
{
	int	i;

	i = 0;
	while (rtnlist[i])
		free(rtnlist[i++]);
	free(rtnlist);
}

static char	**split_logic(char **rtnlist, const char *s, char c, int count)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (j < count)
	{
		len = getstrlen((char *)&s[i], c);
		rtnlist[j] = ft_calloc(len, sizeof(char));
		if (!rtnlist[j])
		{
			free_rtnlist(rtnlist);
			return (NULL);
		}
		ft_strlcpy(rtnlist[j], &s[i], len);
		i += len;
		while ((char)s[i] == c)
			i++;
		j++;
	}
	return (rtnlist);
}

char	**ft_split(char const *s, char c)
{
	char	**rtnlist;
	int		i;
	int		count;

	if (!s)
		return (NULL);
	if (s[0] == '\0')
	{
		rtnlist = ft_calloc(1, sizeof(char *));
		if (!rtnlist)
			return (NULL);
		rtnlist[0] = NULL;
		return (rtnlist);
	}
	i = 0;
	while (s[i] == c)
		i++;
	count = countchar(&s[i], c);
	rtnlist = ft_calloc(count + 1, sizeof(char *));
	if (!rtnlist)
		return (NULL);
	return (split_logic(rtnlist, &s[i], c, count));
}
