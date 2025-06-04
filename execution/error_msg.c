/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:51:48 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/04 11:39:27 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	print_file_err(char *filename, int errnum)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, filename, strlen(filename));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errnum), strlen(strerror(errnum)));
	write(STDERR_FILENO, "\n", 1);
}

int	command_not_found(char **args)
{
	write(2, args[0], ft_strlen(args[0]));
	write(2, ": command not found\n", 20);
	free_matrix(args);
	return (127);
}
