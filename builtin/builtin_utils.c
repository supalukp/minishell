/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:42:19 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/04 15:14:45 by spunyapr         ###   ########.fr       */
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

bool	is_buildin(t_tree *tree)
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

int	exec_buildin(t_tree *tree, t_data *data)
{
	int		exit_status;
	char	**cmd;

	cmd = combine_cmdline(tree->cmd_line);
	if (!ft_strcmp(cmd[0], "echo"))
		exit_status = ft_echo(tree);
	// else if (!ft_strcmp(cmd[0], "cd"))
	//     return (true);
	else if (!ft_strcmp(cmd[0], "pwd"))
		exit_status = ft_pwd(tree);
	else if (!ft_strcmp(cmd[0], "export"))
		exit_status = ft_export(tree, data);
	else if (!ft_strcmp(cmd[0], "unset"))
		exit_status = ft_unset(tree, data);
	else if (!ft_strcmp(cmd[0], "env"))
		exit_status = ft_env(tree, data);
	// else if (!ft_strcmp(cmd[0], "exit"))
	//     return (true);
	else
		return (free_matrix(cmd), 1);
	return (free_matrix(cmd), exit_status);
}
