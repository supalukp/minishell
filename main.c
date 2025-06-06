/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/06/06 15:09:17 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

void	handle_line(char *line, t_data *request)
{
	t_tree	*tree;

	tree = mns_parse(line);
	request->ast = tree;
	if (request->ast)
	{
		print_all(request);
		request->last_exit = main_execution(request->ast, request);
		printf("exit status = %d\n", request->last_exit);
		free_program(request);
	}
}


int	main(int ac, char **av, char **env)
{
	char	*line;
	t_data	request;

	(void)ac;
	(void)av;
	
	init_signals();
	request.env = env_init(env);
	request.last_exit = 0;
	line = readline("> ");
	while (line != NULL)
	{
		add_history(line);
		handle_line(line, &request);
		line = readline("> ");
	}
	if (request.env)
		free_env(request.env);
	// rl_clear_history();
	return (0);
}
