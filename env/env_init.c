/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:22:18 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 14:31:00 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

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
	t_env	*tmp;
	int		level;
	char	*value;

	tmp = env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->env_name, "SHLVL") == 0)
		{
			level = ft_atoi(tmp->env_variable);
			if (level < 0)
				level = 1;
			else
				level++;
			free(tmp->env_variable);
			value = ft_itoa(level);
			tmp->env_variable = value;
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_env_back(&env_lst, create_single_node("SHLVL", "1"));
}

static int	oldpwd_not_exist(t_env *env_lst)
{
	while (env_lst)
	{
		if (ft_strcmp(env_lst->env_name, "OLDPWD") == 0)
			return (0);
		env_lst = env_lst->next;
	}
	return (1);
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
		update_shlvl(env_lst);
		if (oldpwd_not_exist(env_lst))
			ft_lstadd_env_back(&env_lst, create_single_node("OLDPWD", NULL));
	}
	return (env_lst);
}
