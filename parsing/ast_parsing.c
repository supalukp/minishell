/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:16:35 by syukna            #+#    #+#             */
/*   Updated: 2025/06/29 13:38:17 by syukna           ###   ########.fr       */
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

t_tree	*mns_parse(char *line)
{
	t_tree			*request;
	int				error;

	error = 0;
	request = ast_maker(line, &error);
	if (error)
	{
		if (request)
			clean_recursive_tree(request);
		return (NULL);
	}
	return (request);
}
