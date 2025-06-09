/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:16:35 by syukna            #+#    #+#             */
/*   Updated: 2025/06/09 17:31:47 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

t_type	has_operator(char *line, t_type	operator)
{
	int		i;
	int		parenthesis;
	bool	single_q;
	bool	double_q;
	i = 0;
	parenthesis = 0;
	single_q = false;
	double_q = false;
	while (line[i])
	{
		if (line[i]  == '(')
			parenthesis += 1;
		if (line[i]  == ')')
			parenthesis -= 1;
		if (line[i]  == '\'')
		{
			if (single_q == false)
				single_q = true;
			else
				single_q = false;
		}
		if (line[i]  == '\"')
		{
			if (double_q == false)
				double_q = true;
			else
				double_q = false;
		}
		if (operator == PIPE && line[i]  == '|' && line[i - 1]  != '|' && line[i + 1]  != '|' && parenthesis == 0 && single_q == false && double_q == false)
			return (1);
		if (operator == AND && line[i]  == '&' && line[i + 1]  == '&'  && parenthesis == 0 && single_q == false && double_q == false)
			return (1);
		if (operator == OR && line[i]  == '|' && line[i + 1]  == '|'  && parenthesis == 0 && single_q == false && double_q == false)
			return (1);
		i++;
	}
	return (0);
}



t_tree *ast_maker(char *substr, int *error)
{
	t_tree *node;
	
	if (!substr || *error)
		return (NULL);
	node = ft_calloc(1, sizeof(t_tree));
	if (!node)
		return (*error = 1, NULL);
	node->content = NULL;
	if (has_operator(substr, OR))
	{
		node->type = OR;
		parse_separator(substr, node, error);
	}
	else if (has_operator(substr, AND))
	{
		node->type = AND;
		parse_separator(substr, node, error);
	}
	else if (has_operator(substr, PIPE))
	{
		node->type = PIPE;
		parse_separator(substr, node, error);
	}
	else if (contains_letter(substr, '('))
	{
		free(node);
		remove_parenthesis(&substr, error);
		return(ast_maker(substr, error));
	}
	else
	{
		node->content = ft_strtrim(substr, " ");
		if (!node->content)
		{
			free(node);
			return (*error = 1, NULL);
		}
		if (substr)
			free(substr);
		node->type = CMD_LINE;
		command_line_maker(node, error);
		if (*error)
		{
			free(node);
			return (NULL);
		}
	}
	return (node);
}

t_tree	*mns_parse(char *line)
{
	t_tree	*request;
	int				error;

	error = 0;
	request = ast_maker(line, &error);
	printf("Error: %d\n", error);
	if (error)
	{
		if (request)
			clean_recursive_tree(request);
		return (NULL);
	}
	return (request);
}

// 1. split through | || &&  while checking for () overrides
// what about "" and ''?
// 2. if none, go inside the () or "" or ''
// 3. go inside until no more first level operators
// 4. Handle second level operators < > << >>. No need to separate such operators from their FILE

// LOOP through all this 
