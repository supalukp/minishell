/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:08:47 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/02 15:22:20 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    //(void)env;

    t_token *tree;

    tree = NULL;
    pipe_simple_input(&tree);
    //print_ast(tree);

    main_execution(tree, env);
    return (0); 
}