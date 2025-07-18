/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths_absolute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:11:41 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/18 09:31:36 by spunyapr         ###   ########.fr       */
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

static int	check_access_absolute_path(char *path)
{
	struct stat	st;

	if (access(path, X_OK) == -1)
	{
		stderr_msg(path);
		stderr_msg(": Permission denied\n");
		return (126);
	}
	if (access(path, F_OK) == -1)
		return (handle_access_error(path));
	if (stat(path, &st) == 0)
		return (handle_stat_error(path, &st));
	return (0);
}

int	handle_absolute_path(char **args, char **path, char **env)
{
	int	check;

	(void)env;
	check = check_access_absolute_path(args[0]);
	if (check)
		return (check);
	// if (ft_strlen(args[0]) >= PATH_MAX)
	// {
	// 	stderr_msg(args[0]);
	// 	stderr_msg(": File name too long\n");
	// 	return (126);
	// }
	*path = ft_strdup(args[0]);
	if (*path == NULL)
		return (1);
	return (0);
}
