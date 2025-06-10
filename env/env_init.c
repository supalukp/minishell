/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:22:18 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/10 13:18:09 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void    free_matrix(char **matrix)
{
    int i;

    i = 0;
    if (!matrix)
        return ;
    while (matrix[i])
    {
        free(matrix[i]);
        matrix[i] = NULL;
        i++;
    }
    free(matrix);
    matrix = NULL;
}

void    free_matrix(char **matrix)
{
    int i;

    i = 0;
    if (!matrix)
        return ;
    while (matrix[i])
    {
        free(matrix[i]);
        matrix[i] = NULL;
        i++;
    }
    free(matrix);
    matrix = NULL;
}

char	**split_env(char *env)
{
	char	**res;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && env[i] != '=')
		i++;
	res = malloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	res[0] = ft_substr(env, 0, i);
	res[1] = ft_substr(env, i + 1, ft_strlen(env) - i - 1);
	res[2] = NULL;
	return (res);
}

char	**split_env_plus_equal(char *env)
{
	char	**res;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] && env[i] != '+')
		i++;
	if (!(env[i] == '+' && env[i + 1] == '='))
		return (NULL);
	res = malloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	res[0] = ft_substr(env, 0, i);
	res[1] = ft_substr(env, i + 2, ft_strlen(env) - i - 2);
	res[2] = NULL;
	return (res);
}

t_env	*create_single_node(char *env_name, char *env_variable)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->env_name = ft_strdup(env_name);
	new_node->env_variable = ft_strdup(env_variable);
	new_node->next = NULL;
	return (new_node);
}

t_env	*create_own_env(void)
{
	t_env	*own_lst;

	own_lst = malloc(sizeof(t_env));
	if (!own_lst)
		return (NULL);
	own_lst->env_name = ft_strdup("PWD");
	own_lst->env_variable = ft_strdup(getcwd(NULL, 1024));
	own_lst->env_name = ft_strdup("OLDPWD");
	own_lst->env_variable = NULL;
	own_lst->next = malloc(sizeof(t_env));
	own_lst->next->env_name = ft_strdup("SHLVL");
	own_lst->next->env_variable = ft_strdup("1");
	own_lst->next->next = NULL;
	own_lst->next->env_name = ft_strdup("PWD");
	own_lst->next->env_variable = ft_strdup(getcwd(NULL, 1024));
	own_lst->next->next = malloc(sizeof(t_env));
	own_lst->next->next->env_name = ft_strdup("SHLVL");
	own_lst->next->next->env_variable = ft_strdup("1");
	own_lst->next->next->next = NULL;
	return (own_lst);
}

t_env	*env_init(char **env)
{
	t_env	*env_lst;
	t_env	*tmp;
	int		i;

	tmp = NULL;
	env_lst = NULL;
	i = 0;
	if (!env || !env[0])
		env_lst = create_own_env();
	else
	{
		while (env[i])
		{
			tmp = create_env_node(env[i]);
			if (!tmp)
				return (NULL);
			ft_lstadd_env_back(&env_lst, tmp);
			i++;
		}
	}
	return (env_lst);
}
