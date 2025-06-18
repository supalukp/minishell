/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:59:04 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/18 18:16:27 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

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
	count = count_env_node(env_lst);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	tmp = env_lst;
	i = 0;
	while (tmp && i < count)
	{
		res[i] = join_key_value(tmp);
		tmp = tmp->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
