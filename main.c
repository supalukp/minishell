/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:08:47 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/06 11:25:16 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	t_token *tree;

	tree = NULL;
	//one_cmd(&tree);
	pipe_simple_input(&tree);
	// pipe_triple_input(&tree);
	// print_ast(tree);
	// check_if_buildin(tree);
	main_execution(tree, env);
	free_ast(&tree);
	
	return (0);
}