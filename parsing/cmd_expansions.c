/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:11:57 by syukna            #+#    #+#             */
/*   Updated: 2025/06/29 16:49:29 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

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
	if (el->expand_curly_brackets == 2 && el->content[i] == '}')
		i++;
	while (el->content[i])
		rtnstr[j++] = el->content[i++];
	free(el->content);
	el->content = rtnstr;
	trim_space(el);
}

void	expansion_loop(t_cmd_element *cmd, int *count, t_env *lst, t_data *req)
{
	while (includedchar('$', cmd->content) && cmd->quoted != 1 \
		&& *count < counterchar(cmd->content, '$'))
	{
		spec_dol(cmd, count, req->last_exit);
		replace_expansion(cmd, lst, count);
	}
}

int	add_expansions(t_tree *node, t_env *lst, t_data *request)
{
	t_cmd_element	*cmd;
	int				count;

	cmd = node->cmd_line;
	count = 0;
	if (expand_score(node, lst))
		return (0);
	else
	{
		while (cmd)
		{
			add_tild(cmd, lst);
			expansion_loop(cmd, &count, lst, request);
			cmd = cmd->next;
			count = 0;
		}
	}
	return (0);
}
