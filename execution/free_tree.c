/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:42:44 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 16:29:30 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static void	free_file_list(t_file *file)
{
	t_file	*tmp;

	while (file)
	{
		tmp = file->next;
		if (file->content)
			free(file->content);
		free(file);
		file = tmp;
	}
}

void	free_ast(t_tree *node)
{
	t_cmd_element	*tmp_cmd;
	t_cmd_element	*next;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->content)
		free(node->content);
	tmp_cmd = node->cmd_line;
	while (tmp_cmd)
	{
		next = tmp_cmd->next;
		if (tmp_cmd->content)
			free(tmp_cmd->content);
		free(tmp_cmd);
		tmp_cmd = next;
	}
	if (node->files)
		free_file_list(node->files);
	free(node);
}
