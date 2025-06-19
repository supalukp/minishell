/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:59:04 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 10:39:19 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	count_env_not_null_value(t_env *env_lst)
{
	int	count;

	count = 0;
	while (env_lst)
	{
		if (env_lst->env_name && env_lst->env_variable)
			count++;
		env_lst = env_lst->next;
	}
	return (count);
}

int	count_env_node(t_env *env_lst)
{
	int	count;

	count = 0;
	while (env_lst)
	{
		count++;
		env_lst = env_lst->next;
	}
	return (count);
}

static char	*join_key_value(t_env *env_node)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(env_node->env_name, "=");
	res = ft_strjoin(tmp, env_node->env_variable);
	free(tmp);
	return (res);
}

char	**convert_env_lst_double_arrays(t_env *env_lst)
{
	int		count;
	int		i;
	char	**res;
	t_env	*tmp;

	if (!env_lst)
		return (NULL);
	count = count_env_not_null_value(env_lst);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	tmp = env_lst;
	i = 0;
	while (tmp && i < count)
	{
		if (tmp->env_name && tmp->env_variable)
			res[i++] = join_key_value(tmp);
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}

// char	**convert_env_lst_double_arrays(t_env *env_lst)
// {
// 	int		count;
// 	int		i;
// 	char	**res;
// 	t_env	*tmp;

// 	if (!env_lst)
// 		return (NULL);
// 	count = count_env_not_null_value(env_lst);
// 	res = malloc(sizeof(char *) * (count + 1));
// 	if (!res)
// 		return (NULL);
// 	tmp = env_lst;
// 	i = 0;
// 	while (tmp && i < count)
// 	{
// 		if (!tmp->env_name || !tmp->env_variable)
// 		{
// 			tmp = tmp->next;
// 			continue ;
// 		}
// 		res[i] = join_key_value(tmp);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	res[i] = NULL;
// 	return (res);
// }
