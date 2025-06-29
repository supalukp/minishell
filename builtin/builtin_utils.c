/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:42:19 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/23 16:38:27 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

bool	is_builtin(t_tree *tree)
{
	char	**cmd;

	cmd = combine_cmdline(tree->cmd_line);
	if (!ft_strcmp(cmd[0], "echo"))
		return (free_matrix(cmd), true);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (free_matrix(cmd), true);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (free_matrix(cmd), true);
	else if (!ft_strcmp(cmd[0], "export"))
		return (free_matrix(cmd), true);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (free_matrix(cmd), true);
	else if (!ft_strcmp(cmd[0], "env"))
		return (free_matrix(cmd), true);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (free_matrix(cmd), true);
	else
		return (free_matrix(cmd), false);
}

static int	handle_exit(t_tree *tree, t_data *data, char **cmd)
{
	int	status;

	status = ft_exit(tree, data->last_exit);
	if ((status != 127 || data->last_exit == 127))
	{
		free_env(data->env);
		free_matrix(cmd);
		clean_data(data);
		rl_clear_history();
		if (data->last_exit == 127)
			exit(127);
		exit(status);
	}
	return (status);
}

// static int	handle_exit(t_tree *tree, t_data *data, char **cmd)
// {
// 	int	status;

// 	status = ft_exit(tree, data->last_exit);
// 	if ((status != 2 || data->last_exit == 2) && status != 127)
// 	{
// 		free_env(data->env);
// 		free_matrix(cmd);
// 		clean_data(data);
// 		rl_clear_history();
// 		if (data->last_exit == 2)
// 			exit(2);
// 		exit(status);
// 	}
// 	return (status);
// }

int	exec_builtin(t_tree *tree, t_data *data)
{
	int		exit_status;
	char	**cmd;

	exit_status = 0;
	cmd = combine_cmdline(tree->cmd_line);
	if (!ft_strcmp(cmd[0], "echo"))
		exit_status = ft_echo(tree);
	else if (!ft_strcmp(cmd[0], "cd"))
		exit_status = ft_cd(tree, data->env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		exit_status = ft_pwd(tree, data->env);
	else if (!ft_strcmp(cmd[0], "export"))
		exit_status = ft_export(tree, data);
	else if (!ft_strcmp(cmd[0], "unset"))
		exit_status = ft_unset(tree, data);
	else if (!ft_strcmp(cmd[0], "env"))
		exit_status = ft_env(tree, data);
	else if (!ft_strcmp(cmd[0], "exit"))
		exit_status = handle_exit(tree, data, cmd);
	else
		exit_status = 1;
	if (cmd != NULL)
		free_matrix(cmd);
	return (exit_status);
}
