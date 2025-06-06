/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/06/05 18:18:01 by syukna           ###   ########.fr       */
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
	if (request.ast)
	{
		print_all(&request);
		request.last_exit = main_execution(request.ast, &request);
		clean_data(&request);
	}
	// // print_env(request.env);
	// printf( "find var USER = %s\n", find_expansion_match("USER", request.env));
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	line = readline("> ");
	(void)ac;
	(void)av;
	while (line != NULL)
	{
		add_history(line);
		handle_line(line, env);
		line = readline("> ");
	}
	return (0);
}
