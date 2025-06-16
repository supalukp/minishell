/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:11:57 by syukna            #+#    #+#             */
/*   Updated: 2025/06/14 18:30:44 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

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
	return ("");
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
		rtnstr[j++] = new[y++];
	i++;
	while (ft_isalnum(el->content[i]) || el->content[i] == '_')
		i++;
	while (el->content[i])
		rtnstr[j++] = el->content[i++];
	free(el->content);
	el->content = rtnstr;
}

int	current_pos_dollar(char *line, int count)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (j == count)
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

void	replace_expansion(t_cmd_element *line, t_env *lst, int *count)
{
	int 	i;
	int		j;
	int		len;
	char	*searchword;
	char	*rtnvalue;
	int		slashed;

	j = 0;
	slashed = 0;
	i = current_pos_dollar(line->content, *count);
	if (i > 0 && line->content[i - 1] == '\\')
	{
		slashed = 1;
		(*count)++;
		memmove(&line->content[i - 1], &line->content[i], strlen(&line->content[i]) + 1);
		i--;
	}
	i++;
	while (ft_isalnum(line->content[i + j]) || line->content[i + j] == '_')
		j++;
	searchword = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(searchword, &line->content[i], j + 1);
	rtnvalue = find_expansion_match(searchword, lst);
	len = ft_strlen(line->content) - j + ft_strlen(rtnvalue);
	i--;
	free(searchword);
	if (slashed != 1)
		exchange_expansion_values(line, rtnvalue, i, len);
}

int	counterchar(char const *s1, char letter)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s1[i] == letter)
			j++;
		i++;
	}
	return (j);
}

int	add_expansions(t_tree *node, t_env *lst)
{
	t_cmd_element	*cmd;
	int				expansions;
	int				count;

	cmd = node->cmd_line;
	count = 0;
	// add_tild(node, lst);
	while (cmd)
	{
		expansions = counterchar(cmd->content, '$');
		
		while (includedchar('$', cmd->content) && cmd->quoted != 1 && count < counterchar(cmd->content, '$'))
			replace_expansion(cmd, lst, &count);
		cmd = cmd->next;
		count = 0;
	}
	return (0);
}
