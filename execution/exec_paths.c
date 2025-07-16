/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:54:22 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/16 16:55:02 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	path_only_slash(char *path)
{ 
	int	i;

	if (ft_strlen(path) < 2)
		return (0);
	if (!path || path[0] != '.')
		return (0);
	i = 1;
	while (path[i])
	{
		if (path[i] != '/')
			return (0);
		i++;
	}
	return (1);
}

int	prepare_exec_path(char **args, char **path, char **env)
{
	if (args[0][0] == '/')
		return (handle_absolute_path(args, path, env));
	if (path_only_slash(args[0]))
	{
		stderr_msg(args[0]);
		stderr_msg(": Is a directory\n");
		return (126);
	}
	else if (args[0][0] == '.')
		return (handle_relative_path(args, path));
	return (0);
}

char	*get_path(char *command, char **envp)
{
	int		i;
	char	**all_path;

	i = 0;
	if (!command || !envp)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			all_path = ft_split(ft_strchr(envp[i], '=') + 1, ':');
			if (!all_path)
				return (NULL);
			return (find_executable(all_path, command));
		}
		i++;
	}
	return (NULL);
}

char	*find_executable(char **all_path, char *command)
{
	int		j;
	char	*add_slash;
	char	*path_command;

	j = 0;
	while (all_path[j] != NULL)
	{
		add_slash = ft_strjoin(all_path[j], "/");
		if (!add_slash)
			return (free_matrix(all_path), NULL);
		path_command = ft_strjoin(add_slash, command);
		if (!path_command)
			return (free_matrix(all_path), NULL);
		free(add_slash);
		if (access(path_command, F_OK | X_OK) == 0)
		{
			free_matrix(all_path);
			return (path_command);
		}
		free(path_command);
		j++;
	}
	free_matrix(all_path);
	return (NULL);
}
