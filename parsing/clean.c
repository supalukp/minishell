/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:13:39 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 18:18:58 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static void	clean_cmd_line(t_cmd_element *cmd_element)
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

static void	clean_redirections(t_file *file)
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

static void	clean_node(t_tree *node)
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
	node->left = NULL;
	node->right = NULL;
	clean_node(node);
}

void	clean_data(t_data *data)
{
	if (data->ast)
	{
		free_ast(data->ast);
		data->ast = NULL;
	}
}
