/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:16:35 by syukna            #+#    #+#             */
/*   Updated: 2025/05/03 18:57:50 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

t_type	is_operator(char *line)
{
	int i;
	int parenthesis;

	i = 0;
	parenthesis = 0;
	while (line[i])
	{
		if (line[i]  == '(')
			parenthesis += 1;
		if (line[i]  == ')')
			parenthesis -= 1;
		if (line[i]  == '|' && line[i - 1]  != '|' && line[i + 1]  != '|' && parenthesis == 0)
			return (PIPE);
		if (line[i]  == '&' && line[i + 1]  == '&'  && parenthesis == 0)
			return (AND);
		if (line[i]  == '|' && line[i + 1]  == '|'  && parenthesis == 0)
			return (OR);
		i++;
	}
	return (INVALID);
}

t_token *AST_maker(char *substr)
{
	t_token *node;
	t_type	operator;
	
	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL); // TODO = EXIT PROGRAM FUNCTION
	ft_memset(node, '\0', sizeof(t_token));
	operator = is_operator(substr);
	if (operator != INVALID)
	{
		node->content = NULL;
		node->type = operator;
		parse_separator(substr, node);
	}
	else
	{
		node->content = ft_strtrim(substr, " ");
		node->type = CMD;
		// free(substr);
	}
	print_node(node);
	return (node);
	
}

t_token	*mns_parse(char *line)
{
	t_token *request;

	request = AST_maker(line);
	return (request);
}

// 1. split through | || &&  while checking for () overrides
// what about "" and ''?
// 2. if none, go inside the () or "" or ''
// 3. go inside until no more first level operators
// 4. Handle second level operators < > << >>. No need to separate such operators from their FILE

// LOOP through all this 
