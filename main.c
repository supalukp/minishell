/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:08:47 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/27 17:32:35 by spunyapr         ###   ########.fr       */
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
	one_cmd(&tree);
	// try_one_cmd(&tree);
	// pipe_simple_input(&tree);
	// complex_pipe_input(&tree);
	// double_pipes_input(&tree);
	// triple_pipes_input(&tree);
	// quadruple_pipes_input(&tree);
	init_s_main(&data, tree, env);
	// print_ast(tree);
	// print_env(data->env);
	print_export_no_option(data);
	// int i = 0;
	// char *res;
	// while (i < 10)
	// {
	// 	res = create_random_filename();
	// 	printf("%s\n", res);
	// 	free(res);
	// 	i++;
	// }
	// t_env *test = create_own_env();
	// print_env(test);

	// Execution
	// data->last_exit = main_execution(tree, env, data);
	// printf("exit = %d\n", data->last_exit);

	
	// while (str[i])
    // {
    //     if (str[i+1] != NULL && ft_strcmp(str[i], str[i + 1]) > 0)
    //     {
    //         tmp = str[i];
    //         str[i] = str[i + 1];
    //         str[i + 1] = tmp;
	// 		i = 0;
    //     }
	// 	i++;
    // }
	
	
	// FREE
	if (data)
		free_program(data);
	return (0);
}
