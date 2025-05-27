/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:48:10 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/27 17:50:31 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int no_argument(t_tree_token *tree)
{
    t_cmd_element *cmd_lst;
    
    cmd_lst = tree->cmd_line;
    if (cmd_lst->next != NULL)
        return (0);
    else
        return (1);
}

int     count_env_node(t_env *env_lst)
{
    int count;

    count = 0;
    while (env_lst)
    {
        count++;
        env_lst = env_lst->next;
    }
    return (count);
}

t_env **ascii_env_lst(t_data *data)
{
    int i;
    int j;
    int count_env;
    t_env *tmp;
    t_env **ascii_lst;

    i = 0;
    count_env = count_env_node(data->env);
    tmp = data->env;
    ascii_lst = malloc(sizeof(t_env *) * (count_env + 1));
    if (!ascii_lst)
        return (NULL);
    while (tmp)
    {
        ascii_lst[i] = tmp;
        tmp = tmp->next;
        i++;
    }
    ascii_lst[i] = NULL;
    i = 0;
    j = 0;
    while (i < count_env)
    {
        while (j < count_env - i - 1)
        {
            if (ft_strcmp(ascii_lst[j]->env_name, ascii_lst[j + 1]->env_name) > 0)
            {
                tmp = ascii_lst[j];
                ascii_lst[j] = ascii_lst[j + 1];
                ascii_lst[j + 1] = tmp;
            }
            j++;
        }
        j = 0;
        i++;
    }
    return (ascii_lst);
}

