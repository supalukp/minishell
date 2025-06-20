/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_relative.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:11:23 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/20 12:13:21 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	only_dot(char *args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
	{
		if (args[i] == '.' && args[i + 1] == '.')
			return (1);
		else if (args[i] == '.' && args[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

static int	check_access_relative_path(char **args)
{
	struct stat	sb;

	if (only_dot(args[0]))
		return (command_not_found(args));
	if (stat(args[0], &sb) == -1)
		return (command_not_found(args));
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
	*path = ft_strdup(args[0]);
	if (*path == NULL)
		return (1);
	return (0);
}
