/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:33:11 by syukna            #+#    #+#             */
/*   Updated: 2025/06/18 14:59:11 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	clean_cmd_line(t_cmd_element *cmd_element)
{
	t_cmd_element	*first;
	t_cmd_element	*second;

	first = cmd_element;
	while (first->next)
	{
		second = first->next;
		free(first->content);
		free(first);
		first = second;
		second = NULL;
	}
	free(first->content);
	free(first);
}

void	clean_redirections(t_file *file)
{
	t_file	*first;
	t_file	*second;

	first = file;
	while (first->next)
	{
		second = first->next;
		free(first->content);
		free(first);
		first = second;
		second = NULL;
	}
	free(first->content);
	free(first);
}

void	clean_node(t_tree *node)
{
	if (node->cmd_line)
		clean_cmd_line(node->cmd_line);
	if (node->files)
		clean_redirections(node->files);
	free(node);
}

void	clean_recursive_tree(t_tree *node)
{
	if (node->left)
		clean_recursive_tree(node->left);
	if (node->right)
		clean_recursive_tree(node->right);
	clean_node(node);
}

void	clean_data(t_data *data)
{
	if (data->ast)
		clean_recursive_tree(data->ast);
}
