/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:43:18 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/16 16:15:54 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	ft_lstadd_env_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return ;
}

t_env	*create_env_node(char *env_variable)
{
	t_env	*node;
	char	**variable;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	variable = split_env(env_variable);
	if (!variable || !variable[0] || !variable[1])
	{
		free_matrix(variable);
		free(node);
		return (NULL);
	}
	node->env_name = ft_strdup(variable[0]);
	node->env_variable = ft_strdup(variable[1]);
	node->next = NULL;
	free_matrix(variable);
	return (node);
}

t_env	*create_single_node(const char *env_name, char *env_variable)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->env_name = ft_strdup(env_name);
	if (!new_node->env_name)
	{
		free(new_node);
		return (NULL);
	}
	if (env_variable)
	{
		new_node->env_variable = ft_strdup(env_variable);
		if (!new_node->env_variable)
		{
			free(new_node->env_name);
			free(new_node);
			return (NULL);
		}
	}
	else
		new_node->env_variable = NULL;
	new_node->next = NULL;
	return (new_node);
}

// void update_env_underscore(t_env *env_lst, char *cmd_path)
// {
// 	t_env *tmp = env_lst;

// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->env_name, "_") == 0)
// 		{
// 			free(tmp->env_variable);
// 			tmp->env_variable = ft_strdup(cmd_path);
// 			return;
// 		}
// 		tmp = tmp->next;
// 	}
// 	ft_lstadd_env_back(&env_lst, create_single_node("_", cmd_path));
// }
