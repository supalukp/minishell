/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:48:52 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/18 18:14:06 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	unset_variable(char *key, t_data *data)
{
	t_env	*tmp;
	t_env	*env_lst;

	if (!key || !data)
		return (1);
	env_lst = data->env;
	while (env_lst && env_lst->next)
	{
		if (ft_strcmp(env_lst->next->env_name, key) == 0)
		{
			tmp = env_lst->next;
			env_lst->next = env_lst->next->next;
			if (tmp->env_name)
				free(tmp->env_name);
			if (tmp->env_variable)
				free(tmp->env_variable);
			free(tmp);
			return (0);
		}
		else
			env_lst = env_lst->next;
	}
	return (0);
}

static int	unset_process(t_tree *tree, t_data *data)
{
	int				flag;
	t_cmd_element	*args;

	flag = 0;
	args = tree->cmd_line->next;
	if (invalid_option(args, "unset"))
		return (2);
	while (args)
	{
		if (is_exist_variable(args->content, data))
		{
			if (unset_variable(args->content, data))
				flag = 1;
		}
		else if (not_valid_name(args->content, "unset"))
			flag = 1;
		args = args->next;
	}
	return (flag);
}

int	ft_unset(t_tree *tree, t_data *data)
{
	if (no_argument(tree))
		return (0);
	else
		return (unset_process(tree, data));
}
