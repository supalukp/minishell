/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_no_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:34:20 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/20 08:56:32 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	no_argument(t_tree *tree)
{
	t_cmd_element	*cmd_lst;

	cmd_lst = tree->cmd_line;
	if (cmd_lst->next != NULL)
		return (0);
	else
		return (1);
}

static void	sort_env_lst(int count_env, t_env **env_lst)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	j = 0;
	while (i < count_env)
	{
		while (j < count_env - i - 1)
		{
			if (ft_strcmp(env_lst[j]->env_name, env_lst[j + 1]->env_name) > 0)
			{
				tmp = env_lst[j];
				env_lst[j] = env_lst[j + 1];
				env_lst[j + 1] = tmp;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

t_env	**ascii_env_lst(t_data *data)
{
	int		i;
	int		count_env;
	t_env	*tmp;
	t_env	**ascii_lst;

	i = 0;
	count_env = count_env_node(data->env);
	tmp = data->env;
	ascii_lst = malloc(sizeof(t_env *) * (count_env + 1));
	if (!ascii_lst)
		return (NULL);
	while (tmp)
	{
		ascii_lst[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	ascii_lst[i] = NULL;
	sort_env_lst(count_env, ascii_lst);
	return (ascii_lst);
}

int	print_export_no_option(t_data *data)
{
	t_env	**ascii_lst;
	int		i;

	ascii_lst = ascii_env_lst(data);
	i = 0;
	while (ascii_lst[i])
	{
		if (ft_strcmp(ascii_lst[i]->env_name, "_") == 0)
			i++;
		else
		{
			printf("export ");
			printf("%s", ascii_lst[i]->env_name);
			if (ascii_lst[i]->env_variable)
				printf("=\"%s\"\n", ascii_lst[i]->env_variable);
			else
				printf("\n");
			i++;
		}
	}
	free(ascii_lst);
	return (0);
}
