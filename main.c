/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/06/07 17:26:01 by spunyapr         ###   ########.fr       */
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

// int	main(int ac, char **av, char **env)
// {
// 	char	*line;
// 	t_data	request;

// 	(void)ac;
// 	(void)av;
	
// 	init_signals();
// 	request.env = env_init(env);
// 	request.last_exit = 0;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (line == NULL)
// 			break;
// 		if (*line == '\0') 
// 		{
// 			free(line);
// 			continue;
// 		}
// 		add_history(line);
// 		handle_line(line, &request);
// 		free(line);
// 	}
// 	if (request.env)
// 		free_env(request.env);
// 	return (0);
// }

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
