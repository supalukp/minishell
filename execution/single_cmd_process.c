/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:11:00 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/06 14:54:09 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	child_execution(char *paths, char **args, char **minishell_env)
{
	execve(paths, args, minishell_env);
	perror("execve failed");
	free_matrix(minishell_env);
	free_matrix(args);
	free(paths);
	exit(126);
}

int	wait_and_clean(int exit_status, pid_t pid, char **args, char *paths)
{
	if (waitpid(pid, &exit_status, 0) == -1)
	{
		perror("waitpid");
		return (EXIT_FAILURE);
	}
	free_matrix(args);
	free(paths);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	else if (WIFSIGNALED(exit_status))
		return (128 + WTERMSIG(exit_status));
	else
		return (EXIT_FAILURE);
}
