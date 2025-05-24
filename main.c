/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:08:47 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/24 14:13:17 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	t_tree_token *tree;
	t_data *data;

	tree = NULL;
	data = NULL;
	// one_cmd(&tree);
	// try_one_cmd(&tree);
	// pipe_simple_input(&tree);
	complex_pipe_input(&tree);
	// double_pipes_input(&tree);
	// triple_pipes_input(&tree);
	// quadruple_pipes_input(&tree);
	init_s_main(&data, tree);
	print_ast(tree);
	// int i = 0;
	// char *res;
	// while (i < 10)
	// {
	// 	res = create_random_filename();
	// 	printf("%s\n", res);
	// 	free(res);
	// 	i++;
	// }

	// Execution
	main_execution(tree, env, data);
	
	// FREE
	if (data)
		free_program(data);
	return (0);
}
