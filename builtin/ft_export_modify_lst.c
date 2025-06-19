/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_modify_lst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:14:29 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/18 18:15:17 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	create_new_variable(char *args, t_data *data)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->env_name = ft_strdup(args);
	new_node->env_variable = NULL;
	new_node->next = NULL;
	ft_lstadd_env_back(&data->env, new_node);
	return (0);
}

int	add_value_variable(char *args, t_data *data)
{
	char	**env;
	t_env	*env_lst;
	char	*res;

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

int	add_new_variable(char *args, t_data *data)
{
	t_env	*new_node;

	new_node = create_env_node(args);
	if (!new_node)
		return (1);
	ft_lstadd_env_back(&data->env, new_node);
	return (0);
}

int	is_exist_variable(char *args, t_data *data)
{
	t_env	*env_lst;
	char	**env;

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

int	change_value_variable(char *args, t_data *data)
{
	char	**env;
	t_env	*env_lst;

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
