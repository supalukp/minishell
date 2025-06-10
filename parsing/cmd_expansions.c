/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:11:57 by syukna            #+#    #+#             */
/*   Updated: 2025/06/03 18:50:22 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	includedchar(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}
char	*find_expansion_match(const char *search, t_env *lst)
{
	
	while (lst)
	{
		if (ft_strlen(search) == ft_strlen(lst->env_name))
		{
			if (ft_strncmp(search, lst->env_name, ft_strlen(search)) == 0)
				return (lst->env_variable);
		}
		lst = lst->next;
	}
	return (NULL);
}

void	exchange_expansion_values(t_cmd_element *el, char *new, int i, int len)
{
	char	*rtnstr;
	int		j;
	int		y;
	
	j = 0;
	y = 0;
	rtnstr = ft_calloc(len + 1, sizeof(char));
	while (j < i)
	{
		rtnstr[j] = el->content[j];
		j++;
	}
	while (new[y])
	{
		rtnstr[j] = new[y];
		j++;
		y++;
	}
	while (new[y])
		rtnstr[j++] = new[y++];
	i++;
	while (ft_isalnum(el->content[i]))
		i++;
	while (el->content[i])
		rtnstr[j++] = el->content[i++];
	free(el->content);
	el->content = rtnstr;
}

int	replace_expansion(t_cmd_element *line, t_env *lst)
{
	int 	i;
	int		j;
	int		len;
	char	*searchword;
	char	*rtnvalue;

	i = 0;
	j = 0;
	while (line->content[i] != '$')
		i++;
	i++;
	while (ft_isalnum(line->content[i + j]))
		j++;
	searchword = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(searchword, &line->content[i], j + 1);
	rtnvalue = find_expansion_match(searchword, lst);
	len = ft_strlen(line->content) - j + ft_strlen(rtnvalue);
	rtnvalue = ft_calloc(len, sizeof(char));
	rtnvalue = find_expansion_match(searchword, lst);
	i--;
	exchange_expansion_values(line, rtnvalue, i, len);
	return (0);
}

int	add_expansions(t_tree *node, t_env *lst)
{
	t_cmd_element *cmd;

	cmd = node->cmd_line;
	while (cmd)
	{
		while (includedchar('$', cmd->content))
		{
			if (replace_expansion(cmd, lst) == 0)
				return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
