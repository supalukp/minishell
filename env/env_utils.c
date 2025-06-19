/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:20:51 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 09:10:39 by spunyapr         ###   ########.fr       */
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

void	print_env(t_env *lst)
{
	while (lst)
	{
		if (lst->env_variable)
			printf("%s=%s\n", lst->env_name, lst->env_variable);
		lst = lst->next;
	}
}

void	free_env(t_env *env_lst)
{
	t_env	*tmp;

	while (env_lst)
	{
		tmp = env_lst->next;
		if (env_lst->env_name)
			free(env_lst->env_name);
		if (env_lst->env_variable)
			free(env_lst->env_variable);
		if (env_lst)
			free(env_lst);
		env_lst = tmp;
	}
}
