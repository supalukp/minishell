/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/06/14 17:02:59 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

volatile sig_atomic_t g_signal = 0;

void	handle_line(char *line, t_data *request)
{
	t_tree	*tree;
	int	exit_status;
	char *lexer;

	exit_status = error_checking(line, request);
	if (exit_status != 0) 
	{
		request->last_exit = exit_status;
		return;
	}
	if (only_space(line) || only_colon(line) || only_exclamation(line))
		return ;
	lexer = merge_quotes(line);
	free(line);
	tree = mns_parse(lexer);
	if (have_pipes(tree))
		free(lexer);
	request->ast = tree;
	if (request->ast)
	{
		// print_all(request);
		request->last_exit = main_execution(request->ast, request);
		// printf("exit status = %d\n", request->last_exit);
		clean_data(request);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_data	request;
	char *prompt;
	(void)ac;
	(void)av;
	
	// signal(SIGPIPE, SIG_IGN);

	init_signal();
	request.env = env_init(env);
	request.last_exit = 0;
	while (1)
	{
		g_signal = 0;
		prompt = build_prompt(request.last_exit);
		line = readline(prompt);
		if (prompt)
			free(prompt);
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (*line)
			add_history(line);
		handle_line(line, &request);
	}
	if (request.env)
		free_env(request.env);
	if (line)
    	free(line);
	rl_clear_history();
	return (0);
}
