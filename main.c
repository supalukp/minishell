/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/06/04 14:25:47 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

void	handle_line(char *line)
{
	t_tree	*tree;
	t_data	request;

	tree = mns_parse(line);
	request.ast = tree;
	if (request.ast)
	{
		print_all(&request);
		clean_data(&request);
	}
}

int	main(void)
{
	char	*line;

	line = readline("> ");
	while (line != NULL)
	{
		add_history(line);
		handle_line(line);
		line = readline("> ");
	}
	return (0);
}
