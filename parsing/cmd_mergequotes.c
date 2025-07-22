/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mergequotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:22:38 by syukna            #+#    #+#             */
/*   Updated: 2025/07/22 17:41:21 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static void	quotes_merger(t_cmd_element *cmd)
{
	char			*newstr;
	t_cmd_element	*tmpcmd;

	if (!cmd || !cmd->next)
		return ;
	tmpcmd = cmd->next;
	newstr = ft_strjoin(cmd->content, cmd->next->content);
	free(cmd->content);
	cmd->content = newstr;
	cmd->space_after = tmpcmd->space_after;
	cmd->next = tmpcmd->next;
	free(tmpcmd->content);
	free(tmpcmd);
}

void	merge_cmd_quotes(t_tree *node)
{
	t_cmd_element	*cmd;

	if (!node->cmd_line)
		return ;
	cmd = node->cmd_line;
	while (cmd->next)
	{
		if (cmd->space_after == 0)
			quotes_merger(cmd);
		if (cmd->space_after && cmd->next)
			cmd = cmd->next;
	}
}
