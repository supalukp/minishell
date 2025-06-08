/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/06/08 16:52:33 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

void	handle_line(char *line, t_data *request)
{
	t_tree	*tree;
	int	exit_status;

	exit_status = error_checking(line, request);
	if (exit_status != 0) 
	{
		request->last_exit = exit_status;
		return;
	}
	tree = mns_parse(line);
	request->ast = tree;
	if (request->ast)
	{
		print_all(request);
		request->last_exit = main_execution(request->ast, request);
		printf("exit status = %d\n", request->last_exit);
		clean_data(request);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_data	request;
	struct sigaction sa;
	(void)ac;
	(void)av;
	
	sa.sa_handler = handler_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	
	request.env = env_init(env);
	request.last_exit = 0;
	line = readline("> ");
	while (line != NULL)
	{
		printf("%s\n", line);
		add_history(line);
		handle_line(line, &request);
		line = readline("> ");
	}
	if (request.env)
		free_env(request.env);
	if (line)
    	free(line);
	rl_clear_history();
	return (0);
}

