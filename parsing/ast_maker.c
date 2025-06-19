/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:49:13 by syukna            #+#    #+#             */
/*   Updated: 2025/06/19 14:48:43 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	ast_op_state(int *par, bool *q1, bool *q2, char letter)
{
	if (letter == '(')
		*par += 1;
	if (letter == ')')
		*par -= 1;
	if (letter == '\'')
	{
		if (*q1 == false)
			*q1 = true;
		else
			*q1 = false;
	}
	if (letter == '\"')
	{
		if (*q2 == false)
			*q2 = true;
		else
			*q2 = false;
	}
}

t_type	has_operator(char *ss, t_type	op)
{
	int		i;
	int		par;
	bool	q1;
	bool	q2;

	i = 0;
	par = 0;
	q1 = false;
	q2 = false;
	while (ss[i])
	{
		ast_op_state(&par, &q1, &q2, ss[i]);
		if (par == 0 && q1 == false && q2 == false)
		{
			if (op == PIPE && ss[i] == '|')
				if ((i == 0 || ss[i - 1] != '|') && ss[i + 1] != '|')
					return (1);
			if (op == AND && ss[i] == '&' && ss[i + 1] == '&')
				return (1);
			if (op == OR && ss[i] == '|' && ss[i + 1] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

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

t_tree	*ast_maker(char *substr, int *error)
{
	t_tree	*node;

	if (!substr || *error)
		return (NULL);
	node = ft_calloc(1, sizeof(t_tree));
	if (!node)
		return (*error = 1, NULL);
	node->content = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->fd_heredoc = -1;
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
