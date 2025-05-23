/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:16:35 by syukna            #+#    #+#             */
/*   Updated: 2025/05/22 15:39:35 by syukna           ###   ########.fr       */
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

t_tree_token *ast_maker(char *substr)
{
	t_tree_token *node;
	t_type	operator;
	
	if (!substr)
		return (NULL);
	node = malloc(sizeof(t_tree_token));
	if (!node)
		return (NULL); // TODO = EXIT PROGRAM FUNCTION
	// TODO need to trim string here
	ft_memset(node, '\0', sizeof(t_tree_token));
	operator = is_operator(substr);
	if (operator != INVALID)
	{
		node->content = NULL;
		node->type = operator;
		parse_separator(substr, node);
	}
	else if (contains_letter(substr, '('))
	{
		remove_parenthesis(&substr);
		return(ast_maker(substr));
	}
	else
	{
		node->content = ft_strtrim(substr, " ");
		node->type = CMD_LINE;
		command_line_maker(node);
		// free(substr);
	}
	return (node);
}

t_tree_token	*mns_parse(char *line)
{
	t_tree_token *request;

	request = ast_maker(line);
	return (request);
}

// 1. split through | || &&  while checking for () overrides
// what about "" and ''?
// 2. if none, go inside the () or "" or ''
// 3. go inside until no more first level operators
// 4. Handle second level operators < > << >>. No need to separate such operators from their FILE

// LOOP through all this 
