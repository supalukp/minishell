/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/05/03 18:18:32 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

void	handle_line(char *line)
{
	t_token	*request;

	request = mns_parse(line);

	printf("The chosen node = \n");
	print_node(request);
}

int main(void)
{
	char	*line;
	while((line = readline("> ")) != NULL)
	{
		handle_line(line);
		add_history(line);
		free(line);
	}
	return (0);
}
