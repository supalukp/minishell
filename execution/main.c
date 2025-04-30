/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:26:49 by spunyapr          #+#    #+#             */
/*   Updated: 2025/04/30 16:07:43 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headings.h"

int main (int ac, char **av, char **env)
{
    t_token *tree;
    t_env *env_lst;

    
    // Parsing
    /*  
        transform input to token
        store it in tree
    */
    init_env();
    pipe_simple_input(tree);
    
    // Execution
    main_execution(tree);
    
}
