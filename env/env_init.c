/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:22:18 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/18 18:20:49 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

char	**split_env(const char *env)
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

char	**split_env_plus_equal(const char *env)
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

static t_env	*create_own_env(void)
{
	t_env	*own_lst;

	own_lst = create_single_node("PWD", getcwd(NULL, 0));
	if (!own_lst)
		return (NULL);
	own_lst->next = create_single_node("OLDPWD", NULL);
	if (!own_lst->next)
	{
		free_env(own_lst);
		return (NULL);
	}
	own_lst->next->next = create_single_node("SHLVL", "1");
	if (!own_lst->next->next)
	{
		free_env(own_lst);
		return (NULL);
	}
	return (own_lst);
}

static void	update_shlvl(t_env *env_lst)
{
	int		level;
	char	*value;
	bool	found;
	t_env	*tmp;

	found = false;
	tmp = env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->env_name, "SHLVL") == 0)
		{
			found = true;
			level = ft_atoi(tmp->env_variable);
			if (level < 0)
			{
				value = ft_itoa(1);
				tmp->env_variable = value;
			}
			else
			{
				level++;
				free(tmp->env_variable);
				value = ft_itoa(level);
				tmp->env_variable = value;
			}
			break ;
		}
		tmp = tmp->next;
	}
	if (!found)
		ft_lstadd_env_back(&env_lst, create_single_node("SHLVL", "1"));
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
	update_shlvl(env_lst);
	return (env_lst);
}
