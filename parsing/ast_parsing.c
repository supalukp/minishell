/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:16:35 by syukna            #+#    #+#             */
/*   Updated: 2025/06/18 13:49:51 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

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
