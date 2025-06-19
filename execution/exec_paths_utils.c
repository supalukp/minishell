/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:02:31 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 11:03:31 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

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
