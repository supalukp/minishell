/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:11:00 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 23:14:46 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	child_execution(char *paths, char **args, char **minishell_env,
		t_data *data)
{
	(void)data;
	if (args[0][0] == '\0')
	{
		write(2, " ",1);
		write(2, ": command not found\n", 20);
		free_matrix(args);
		free(paths);
		free_matrix(minishell_env);
		free_program(data);
		exit (127);
	}
	execve(paths, args, minishell_env);
	perror("execve failed");
	free_matrix(minishell_env);
	if (args)
		free_matrix(args);
	if (paths)
		free(paths);
	free_program(data);
	exit(126);
}

int	wait_and_clean(int exit_status, pid_t pid, char **args, char *paths)
{
	if (waitpid(pid, &exit_status, 0) == -1)
	{
		perror("waitpid");
		return (EXIT_FAILURE);
	}
	if (args)
		free_matrix(args);
	if (paths)
		free(paths);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	else if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(exit_status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
		return (128 + WTERMSIG(exit_status));
	}
	else
		return (EXIT_FAILURE);
}
