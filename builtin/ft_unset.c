/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:48:52 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 10:01:06 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	unset_head_node(const char *key, t_data *data)
{
	t_env	*tmp;

	if (ft_strcmp(data->env->env_name, key) == 0)
	{
		tmp = data->env;
		data->env = data->env->next;
		if (tmp->env_name)
			free(tmp->env_name);
		if (tmp->env_variable)
			free(tmp->env_variable);
		free(tmp);
		return (0);
	}
	return (1);
}

static int	unset_variable(char *key, t_data *data)
{
	t_env	*tmp;
	t_env	*env_lst;

	if (!key || !data || !data->env)
		return (1);
	if (unset_head_node(key, data) == 0)
		return (0);
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

int	unset_not_valid_name(char *args, char *function)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	(void)function;
	if (args[i] == '=' || args[i] == '?')
		return (0);
	while (args[i] && args[i] != '=' && !(args[i] == '+' && args[i + 1] == '='))
	{
		if (i == 0 && (args[i] != '_' && !ft_isalpha(args[i])))
			return (0);
		else if (args[i] != '_' && !ft_isalnum(args[i]))
			return (0);
		else
			i++;
	}
	return (flag);
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
		else if (unset_not_valid_name(args->content, "unset"))
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
