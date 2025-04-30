/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:16:35 by syukna            #+#    #+#             */
/*   Updated: 2025/04/30 16:04:43 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"
// #include "../inc/structures.h"

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

t_token	mns_parse(char *line)
{
	t_token request;
	
	ft_memset(&request, '\0', sizeof(t_token));
	printf("Got = %s\n", line);
	printf("With enum = %u\n", is_operator(line));
	if (is_operator(line) != INVALID)
		printf("WE HAVE AN OPERATOR\n");
	return (request);
}

// 1. split through | || &&  while checking for () overrides
// what about "" and ''?
// 2. if none, go inside the () or "" or ''
// 3. go inside until no more first level operators
// 4. Handle second level operators < > << >>. No need to separate such operators from their FILE

// LOOP through all this 
