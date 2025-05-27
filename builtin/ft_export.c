/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:34:42 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/27 18:26:33 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

/* 
Rules for valid variable names:
- Must start with a letter or underscore (`_`)
- Can contain letters, digits, or underscores
- Cannot contain spaces, dashes, or special characte
*/

int print_export_no_option(t_data *data)
{
    t_env **ascii_lst;
    int i;

    ascii_lst = ascii_env_lst(data);
    i = 0;
    while (ascii_lst[i])
    {
        if (ft_strcmp(ascii_lst[i]->env_name, "_") == 0)
            i++;
        // else if (ascii_lst[i]->env_variable == NULL || ascii_lst[i]->env_variable[i] == '\0')
        //     i++;
        else
        {
            printf("declare -x ");
            printf("%s=%s\n", ascii_lst[i]->env_name, ascii_lst[i]->env_variable);
            i++;
        }
    }
    free(ascii_lst);
    return (0);
}

int string_with_equal(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

int not_valid_variable(t_tree_token *tree)
{
    char **args;
    int i;
    int invalid_flag;

    args = combine_cmdline(tree->cmd_line);
    i = 1;
    invalid_flag = 0;
    while (args[i])
    {
        if (args[i][0] == '-')
        {
            invalid_flag = 1;
            if (i == 1)
            {
                ft_putstr_fd("export: invalid option\n", 2);
                return (2);
            }
            else
                ft_putstr_fd("export: not a valid identifier\n", 2);
        }
        else if (string_with_equal(args[i]))
        {
            if (is_valid_var_name())
                store_good_var_name();
            else
            {
                invalid_flag = 1;
                ft_putstr_fd("export: not a valid identifier\n", 2);
            }
        }
        i++;
    }
}

int ft_export(t_tree_token *tree, t_data *data)
{
    
    if (no_argument(tree))
        return (print_export_no_option(data));
    else
    {
        if (check_valid_variable())
        {
            
            return (1);
        }
        // else if (+=)
        //     change_variable();
        // else if (=)
        // {
        //     create_node();
        //     add_back();
        // }
    }
    return (0);
}
