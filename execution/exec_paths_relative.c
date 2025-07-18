/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths_relative.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:11:23 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/18 09:31:43 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	only_dot(char *args)
{
	if (!args)
		return (0);
	if (!ft_strcmp(args, ".") || !ft_strcmp(args, ".."))
		return (1);
	return (0);
}

static int	check_access_relative_path(char **args)
{
	struct stat	sb;

	if (only_dot(args[0]))
		return (filename_argument_required());
	if (stat(args[0], &sb) == -1)
		return (no_file_or_directory(args));
	if (S_ISDIR(sb.st_mode))
	{
		stderr_msg(args[0]);
		stderr_msg(": Is a directory\n");
		return (126);
	}
	if (!(sb.st_mode & S_IXUSR))
	{
		stderr_msg(args[0]);
		stderr_msg(": Permission denied\n");
		return (126);
	}
	return (0);
}

int	handle_relative_path(char **args, char **path)
{
	int	check;

	check = check_access_relative_path(args);
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
