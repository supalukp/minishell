/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:35:34 by syukna            #+#    #+#             */
/*   Updated: 2025/07/17 12:11:53 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	rem_empty_single_exp(t_tree *node, t_cmd_element *after)
{
	t_cmd_element	*prev;

	prev = node->cmd_line;
	if (prev == after)
	{
		free(after->content);
		free(after);
		node->cmd_line = NULL;
	}
	while (prev->next != after)
		prev = prev->next;
	if (after->next)
		prev->next = after->next;
	else
		prev->next = NULL;
	free(after->content);
	free(after);
}

void	remove_empt_exp(t_tree *cmd_line)
{
	t_cmd_element	*tmp;

	tmp = cmd_line->cmd_line;
	while (tmp)
	{
		if (tmp->content[0] == '\0')
		{
			rem_empty_single_exp(cmd_line, tmp);
			tmp = cmd_line->cmd_line;
		}
		tmp = tmp->next;
	}
}

void	command_line_maker(t_tree *cmd_line, int *error, t_data *request)
{
	if (cmd_line->type != CMD_LINE)
		return ;
	identify_redirections(cmd_line, error);
	remove_quotes_redirections(cmd_line);
	split_cmd_elements(cmd_line, error);
	if (*error)
		return ;
	add_expansions(cmd_line, request->env, request);
	remove_empt_exp(cmd_line);
	merge_cmd_quotes(cmd_line);
}
