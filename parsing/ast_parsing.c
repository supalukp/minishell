/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:16:35 by syukna            #+#    #+#             */
/*   Updated: 2025/06/19 14:37:54 by spunyapr         ###   ########.fr       */
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
