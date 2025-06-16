/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prelexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:29:23 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/09 16:36:37 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	is_quote(char character)
{
	if (character == '\'' || character == '"')
		return (1);
	return (0);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	append_str(char **dest, const char *src)
{
	char	*new_str;

	if (*dest == NULL)
	{
		*dest = ft_strdup(src);
		if (!*dest)
			return ;
	}
	else
	{
		new_str = ft_strjoin(*dest, src);
		if (!new_str)
			return ;
		free(*dest);
		*dest = new_str;
	}
}

int have_pipes(t_tree *tree)
{
	while (tree)
	{
		if (tree->type == PIPE)
			return (1);
		tree = tree->left;
	}
	return (0);
}
