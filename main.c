/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/06/05 17:15:09 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

void	handle_line(char *line, char **env)
{
	t_tree	*tree;
	t_data	request;

	tree = mns_parse(line);
	request.ast = tree;
	request.env = env_init(env);
	request.last_exit = 0;
	if (request.ast)
	{
		print_all(&request);
		request.last_exit = main_execution(request.ast, &request);
		free_program(&request);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	
	char	*line;

	line = readline("> ");
	while (line != NULL)
	{
		add_history(line);
		handle_line(line, env);
		line = readline("> ");
	}
	return (0);
}
