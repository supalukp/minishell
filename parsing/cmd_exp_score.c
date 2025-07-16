/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exp_score.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:43:55 by syukna            #+#    #+#             */
/*   Updated: 2025/07/16 20:54:45 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	expand_score(t_tree *node, t_env *lst)
{
	t_cmd_element	*score;
	t_cmd_element	*cmd;

	cmd = node->cmd_line;
	if (cmd && cmd->next && !ft_strcmp(cmd->content, "cd") && !ft_strcmp(cmd->next->content, "-") \
			&& !cmd->next->next)
	{
		score = node->cmd_line->next;
		while (lst)
		{
			if (ft_strlen(lst->env_name) == 6)
			{
				if (ft_strncmp("OLDPWD", lst->env_name, 6) == 0)
				{
					free(score->content);
					score->content = ft_strdup(lst->env_variable);
					return (1);
				}
			}
			lst = lst->next;
		}
	}
	return (0);
}
