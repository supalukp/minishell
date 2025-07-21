/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_path_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:39:46 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/21 11:36:20 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	dot_error_msg(int flag, char **path)
{
	if (flag == 2)
	{
		write(2, ".: filename argument required\n", 30);
		return (2);
	}
	else if (flag == 127)
	{
		write(2, path[0], ft_strlen(path[0]));
		write(2, " : command not found\n", 21);
		return (127);
	}
	return (0);
}

int	no_file_or_directory(char **args)
{
	write(2, args[0], ft_strlen(args[0]));
	write(2, ": No such file or directory\n", 29);
	return (127);
}

int	command_not_found(char **args)
{
	write(2, args[0], ft_strlen(args[0]));
	write(2, ": command not found\n", 20);
	return (127);
}
