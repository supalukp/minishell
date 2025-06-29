/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:49:13 by syukna            #+#    #+#             */
/*   Updated: 2025/06/29 13:38:11 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	ast_breaker(char *substr, t_tree *node, int *error)
{
	if (has_operator(substr, OR))
	{
		node->type = OR;
		parse_separator(substr, node, error);
		return (1);
	}
	else if (has_operator(substr, AND))
	{
		node->type = AND;
		parse_separator(substr, node, error);
		return (1);
	}
	else if (has_operator(substr, PIPE))
	{
		node->type = PIPE;
		parse_separator(substr, node, error);
		return (1);
	}
	return (0);
}

void	ast_cmd_line(char *substr, t_tree *node, int *error)
{
	node->content = ft_strtrim(substr, " ");
	if (!node->content)
	{
		free(node);
		*error = 1;
		return ;
	}
	node->type = CMD_LINE;
}

void	ast_init_node(t_tree *node)
{
	node->content = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->fd_heredoc = -1;
}

t_tree	*ast_maker(char *substr, int *error)
{
	t_tree	*node;

	if (!substr || *error)
		return (NULL);
	node = ft_calloc(1, sizeof(t_tree));
	if (!node)
		return (*error = 1, NULL);
	ast_init_node(node);
	if (!ast_breaker(substr, node, error))
	{
		if (contains_letter(substr, '('))
		{
			remove_parenthesis(&substr, error);
			free(node);
			return (ast_maker(substr, error));
		}
		else
			ast_cmd_line(substr, node, error);
	}
	if (substr)
		free(substr);
	if (*error)
		return (NULL);
	return (node);
}
