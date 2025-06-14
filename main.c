/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/06/12 18:18:37 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

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
	if (only_space(line))
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
	
	init_signal();
	request.env = env_init(env);
	request.last_exit = 0;
	while (1)
	{
		prompt = build_prompt(request.last_exit);
		line = readline(prompt);
		if (prompt)
			free(prompt);
		if (line == NULL)
			break;
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
