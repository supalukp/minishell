/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:16:35 by syukna            #+#    #+#             */
/*   Updated: 2025/05/28 15:41:22 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

t_type	is_operator(char *line)
{
	int i;
	int parenthesis;
	bool	single_q;
	bool double_q;

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
		if (line[i]  == '|' && line[i - 1]  != '|' && line[i + 1]  != '|' && parenthesis == 0 && single_q == false && double_q == false)
			return (PIPE);
		if (line[i]  == '&' && line[i + 1]  == '&'  && parenthesis == 0 && single_q == false && double_q == false)
			return (AND);
		if (line[i]  == '|' && line[i + 1]  == '|'  && parenthesis == 0 && single_q == false && double_q == false)
			return (OR);
		i++;
	}
	return (INVALID);
}

t_tree *ast_maker(char *substr, int *error)
{
	t_tree *node;
	t_type	operator;
	
	if (!substr || *error)
		return (NULL);
	node = ft_calloc(1, sizeof(t_tree));
	if (!node)
		return (*error = 1, NULL);
	operator = is_operator(substr);
	if (operator != INVALID)
	{
		node->content = NULL;
		node->type = operator;
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
