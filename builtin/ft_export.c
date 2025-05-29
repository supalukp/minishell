/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:34:42 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/29 18:08:06 by spunyapr         ###   ########.fr       */
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
        // else if (string_with_equal(args[i]))
        // {
        //     if (is_valid_var_name())
        //         store_good_var_name();
        //     else
        //     {
        //         invalid_flag = 1;
        //         ft_putstr_fd("export: not a valid identifier\n", 2);
        //     }
        // }
        i++;
    }
    return (0);
}

int count_equal(t_cmd_element *args)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (args)
    {
        i = 0;
        while (args->content[i])
        {
            if (args->content[i] == '=')
                count++;
            i++;
        }
        args = args->next;
    }
    return (count);
}

int have_equal(char *str)
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

int export_invalid_option(t_cmd_element *args)
{
    if (args->content[0] == '-')
    {
        ft_putstr_fd("export: invalid option\n", 2);
        return (1);
    }
    return (0);
}

int not_valid_name(char *args)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while (args[i] != '=' && !(args[i] == '+' && args[i + 1] == '='))
    {
        printf("%c\n", args[i]);
        if (i == 0 && (args[i] != '_' && !ft_isalpha(args[i])))
        {
            ft_putstr_fd("export: not a valid identifier\n", 2);
            return (1);
        }
        else if (args[i] != '_' && !ft_isalnum(args[i]))
        {
            ft_putstr_fd("export: not a valid identifier\n", 2);
            return (1);
        }
        else
            i++;
    }
    return (flag);
}

int is_plus_equal(char *args)
{
    int i;

    i = 0;
    while (args[i])
    {
        if (args[i] == '+' && args[i + 1] == '=')
            return (1);
        else if (args[i] == '+' && args[i] != '=')
            return (0);       
        i++;
    }
    return (0);
}

int add_value_variable(char *args, t_data *data)
{
    char **env;
    t_env *env_lst;
    char *res;

    env = split_env_plus_equal(args);
    env_lst = data->env;
    if (!env)
        return (1);
    while (env_lst)
    {
        if (ft_strcmp(env_lst->env_name, env[0]) == 0)
        {
            res = ft_strjoin(env_lst->env_variable, env[1]);
            free(env_lst->env_variable);
            env_lst->env_variable = ft_strdup(res);
            free(res);
            free_matrix(env);
            return (0);
        }
        env_lst = env_lst->next;   
    }
    free_matrix(env);
    return (1);
}

int add_new_variable(char *args, t_data *data)
{
    t_env *new_node;

    new_node = create_env_node(args);
    if (!new_node)
        return (1);
    ft_lstadd_env_back(&data->env, new_node);    
    return (0);
}


int is_exist_variable(char *args, t_data *data)
{
    t_env *env_lst;
    char **env;

    env_lst = data->env;
    env = split_env(args);
    while (env_lst)
    {
        if (ft_strcmp(env_lst->env_name, env[0]) == 0)
        {
            free_matrix(env);
            return (1);
        }
        env_lst = env_lst->next;
    }
    free_matrix(env);
    return (0);
}

int change_value_variable(char *args, t_data *data)
{
    char **env;
    t_env *env_lst;

    env = split_env(args);
    env_lst = data->env;
    if (!env)
        return (1);
    while (env_lst)
    {
        if (ft_strcmp(env_lst->env_name, env[0]) == 0)
        {
            free(env_lst->env_variable);
            env_lst->env_variable = ft_strdup(env[1]);
            free_matrix(env);
            return (0);
        }
        env_lst = env_lst->next;   
    }
    free_matrix(env);
    return (1);
}

int process_export(char *args, t_data *data)
{
    int flag;

    flag = 0;
    if (is_plus_equal(args)) 
    {
        flag = add_value_variable(args, data);
    }
    else if (is_exist_variable(args, data))
    {
        flag = change_value_variable(args, data);
    }
    else
        flag = add_new_variable(args, data);
    return (flag);
}

int process_arguments(t_tree_token *tree, t_data *data)
{
    int flag;
    t_cmd_element *args;

    flag = 0;
    args = tree->cmd_line->next;
    if (export_invalid_option(args))
        return (2);
    else if (count_equal(args) != 0)
    {
        while (args)
        {
            printf("sss\n");
            if (have_equal(args->content))
            {
                if (not_valid_name(args->content))
                {
                    flag = 1;
                }
                else
                    flag = process_export(args->content, data);
            }
            args = args->next;
        }
    }
    else 
        return (0);
    return (flag);
}

int ft_export(t_tree_token *tree, t_data *data)
{
    if (no_argument(tree))
        return (print_export_no_option(data));
    else
        return (process_arguments(tree, data));
    return (0);
}
