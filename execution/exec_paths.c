/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:54:22 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 09:12:11 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	handle_access_error(char *path)
{
	if (errno == ENOENT)
	{
		stderr_msg(path);
		stderr_msg(": No such file or directory\n");
		return (127);
	}
	else if (errno == EACCES)
	{
		stderr_msg(path);
		stderr_msg(": Permission denied\n");
		return (126);
	}
	else if (errno == ENOTDIR)
	{
		stderr_msg(path);
		stderr_msg(": Not a directory\n");
		return (126);
	}
	return (1);
}

static int	handle_stat_error(char *path, struct stat *st)
{
	if (S_ISDIR(st->st_mode))
	{
		stderr_msg(path);
		stderr_msg(": Is a directory\n");
		return (126);
	}
	return (0);
}

int	check_access_path(char *path)
{
	struct stat	st;

	if (access(path, F_OK) == -1)
		return (handle_access_error(path));
	if (stat(path, &st) == 0)
		return (handle_stat_error(path, &st));
	return (0);
}

char	*get_program_name(char *path)
{
	char	**split;
	char	*res;
	int		count;
	int		i;

	count = 0;
	split = ft_split(path, '/');
	if (!split)
		return (NULL);
	while (split[count])
		count++;
	res = ft_strdup(split[count - 1]);
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	return (res);
}

static int	handle_absolute_path(char **args, char **path, char **env)
{
	char	*program_name;
	int		check;

	check = check_access_path(args[0]);
	if (check)
	{
		free_matrix(env);
		free_matrix(args);
		return (check);
	}
	program_name = get_program_name(args[0]);
	free(args[0]);
	args[0] = program_name;
	if (init_path(path, args, env))
		return (127);
	return (0);
}

static void	handle_relative_path(char **args, char **path)
{
	char	*program_name;

	*path = ft_strdup(args[0]);
	program_name = get_program_name(args[0]);
	free(args[0]);
	args[0] = program_name;
}

int	prepare_exec_path(char **args, char **path, char **env)
{
	if (args[0][0] == '/')
		return (handle_absolute_path(args, path, env));
	else if (args[0][0] == '.')
		handle_relative_path(args, path);
	return (0);
}

// int	prepare_exec_path(char **args, char **path, char **env)
// {
// 	char	*program_name;
// 	int		check;

// 	if (args[0][0] == '/')
// 	{
// 		check = check_access_path(args[0]);
// 		if (check)
// 		{
// 			free_matrix(env);
// 			free_matrix(args);
// 			return (check);
// 		}
// 		program_name = get_program_name(args[0]);
// 		free(args[0]);
// 		args[0] = program_name;
// 		if (init_path(path, args, env))
// 			return (127);
// 	}
// 	else if (args[0][0] == '.')
// 	{
// 		*path = ft_strdup(args[0]);
// 		program_name = get_program_name(args[0]);
// 		free(args[0]);
// 		args[0] = program_name;
// 	}
// 	return (0);
// }

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
	return (free_matrix(all_path), NULL);
}
