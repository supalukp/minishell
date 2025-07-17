/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_traverse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:41:43 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/17 14:47:27 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	close_all_heredoc_fd(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type == PIPE || tree->type == OR || tree->type == AND)
	{
		close_all_heredoc_fd(tree->left);
		close_all_heredoc_fd(tree->right);
	}
	else if (tree->type == CMD_LINE)
	{
		if (tree->fd_heredoc != -1)
			close(tree->fd_heredoc);
	}
}

int	traverse_heredoc(t_tree *tree, t_data *data)
{
	int		status;
	t_tree	*node;
	t_file	*file;
	int		error;

	error = 0;
	node = tree;
	if (node == NULL)
		return (0);
	if (node->type == PIPE || node->type == OR || node->type == AND)
	{
		status = traverse_heredoc(node->left, data);
		if (status != 0)
			return (status);
		status = traverse_heredoc(node->right, data);
		if (status != 0)
			return (status);
	}
	else if (node->type == CMD_LINE)
	{
		command_line_maker(node, &error, data);
		file = node->files;
		while (file)
		{
			if (file->type == HEREDOC)
			{
				status = redirect_heredoc(file, node);
				if (status != 0)
				{
					close_all_heredoc_fd(tree);
					return (status);
				}
			}
			file = file->next;
		}
	}
	return (0);
}
