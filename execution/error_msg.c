/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:51:48 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/20 12:01:34 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	print_file_err(const char *filename, int errnum)
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
	return (127);
}

void	stderr_msg(const char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
}

void	error_free_pipes(const char *err_msg, t_pipes *pipes)
{
	stderr_msg(err_msg);
	if (pipes->pipefd)
		free_double_array(pipes->pipefd);
	if (pipes)
		free(pipes);
}

int	perror_free_pipes(const char *err_msg, t_pipes *pipes)
{
	perror(err_msg);
	free_pipes_struct(pipes);
	return (EXIT_FAILURE);
}
