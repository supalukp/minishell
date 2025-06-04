/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:22:18 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/04 08:51:32 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

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
	t_env	*old_lst;
	t_env	*pwd_lst;
	t_env	*shlvl_lst;

	old_lst = create_single_node("OLDPWD", NULL);
	if (!old_lst)
		return (NULL);
	pwd_lst = create_single_node("PWD", getcwd(NULL, 0));
	if (!pwd_lst)
	{
		free_env(old_lst);
		return (NULL);
	}
	ft_lstadd_env_back(&old_lst, pwd_lst);
	shlvl_lst = create_single_node("SHLVL", "1");
	if (!shlvl_lst)
	{
		free_env(old_lst);
		return (NULL);
	}
	ft_lstadd_env_back(&old_lst, shlvl_lst);
	return (old_lst);
}

// t_env	*create_own_env(void)
// {
// 	t_env	*old_lst;
// 	t_env	*pwd_lst;
// 	t_env	*shlvl_lst;

// 	old_lst = malloc(sizeof(t_env));
// 	if (!old_lst)
// 		return (NULL);
// 	old_lst->env_name = ft_strdup("OLDPWD");
// 	old_lst->env_variable = NULL;
// 	pwd_lst = malloc(sizeof(t_env));
// 	if (!pwd_lst)
// 	{
// 		free_env(old_lst);
// 		return (NULL);
// 	}
// 	pwd_lst->env_name = ft_strdup("PWD");
// 	pwd_lst->env_variable = ft_strdup(getcwd(NULL, 0));
// 	old_lst->next = pwd_lst;
// 	shlvl_lst = malloc(sizeof(t_env));
// 	if (!shlvl_lst)
// 	{
// 		free_env(old_lst);
// 		return (NULL);
// 	}
// 	shlvl_lst->env_name = ft_strdup("SHLVL");
// 	shlvl_lst->env_variable = ft_strdup("1");
// 	shlvl_lst->next = NULL;
// 	pwd_lst->next = shlvl_lst;
// 	return (old_lst);
// }

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
