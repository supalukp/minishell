/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:20:51 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 10:44:17 by spunyapr         ###   ########.fr       */
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
