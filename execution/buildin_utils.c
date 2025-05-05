/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:22:31 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/05 16:29:10 by spunyapr         ###   ########.fr       */
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

bool	is_buildin(char *args)
{
	char	**cmd;

	cmd = ft_split(args, ' ');
	if (!ft_strcmp(cmd[0], "echo"))
		return (free(cmd), true);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (free(cmd), true);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (free(cmd), true);
	else if (!ft_strcmp(cmd[0], "export"))
		return (free(cmd), true);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (free(cmd), true);
	else if (!ft_strcmp(cmd[0], "env"))
		return (free(cmd), true);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (free(cmd), true);
	else
		return (free(cmd), false);
}

int	exec_buildin(char *args)
{
	int		exit_status;
	char	**cmd;

	cmd = ft_split(args, ' ');
	if (!ft_strcmp(cmd[0], "echo"))
	{
		exit_status = ft_echo(args);
	}
	// else if (!ft_strcmp(cmd[0], "cd"))
	//     return (true);
	// else if (!ft_strcmp(cmd[0], "pwd"))
	//     return (true);
	// else if (!ft_strcmp(cmd[0], "export"))
	//     return (true);
	// else if (!ft_strcmp(cmd[0], "unset"))
	//     return (true);
	// else if (!ft_strcmp(cmd[0], "env"))
	//     return (true);
	// else if (!ft_strcmp(cmd[0], "exit"))
	//     return (true);
	else
		return (free(cmd), 1);
	return (free(cmd), exit_status);
}
