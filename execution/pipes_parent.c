/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:14:54 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/18 09:16:45 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	close_all_pipes(t_pipes *pipes)
{
	int	i;

	i = -1;
	while (++i < pipes->pipes_count)
	{
		close(pipes->pipefd[i][0]);
		close(pipes->pipefd[i][1]);
	}
}

static void	handle_signal_status(int status, int *sig_printed)
{
	if (WIFSIGNALED(status))
	{
		if (!*sig_printed)
		{
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			else if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit (core dumped)\n", 20);
			*sig_printed = 1;
		}
	}
}

static void	update_exit_status(pid_t pid, pid_t last_pid, int status,
		int *last_exit_status)
{
	if (pid != last_pid)
		return ;
	if (WIFEXITED(status))
		*last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*last_exit_status = 128 + WTERMSIG(status);
}

static int	wait_for_children(t_pipes *pipes)
{
	int		i;
	int		status;
	pid_t	pid;
	pid_t	last_pid;
	int		sig_printed;

	i = 0;
	sig_printed = 0;
	pipes->last_exit_status = 0;
	last_pid = pipes->pid[pipes->process - 1];
	while (i < pipes->process)
	{
		pid = waitpid(pipes->pid[i], &status, 0);
		if (pid == -1)
			perror("waitpid");
		handle_signal_status(status, &sig_printed);
		update_exit_status(pid, last_pid, status, &pipes->last_exit_status);
		i++;
	}
	return (pipes->last_exit_status);
}

int	process_parent(t_pipes *pipes)
{
	int	last_exit_status;

	close_all_pipes(pipes);
	last_exit_status = wait_for_children(pipes);
	free_pipes_struct(pipes);
	return (last_exit_status);
}
