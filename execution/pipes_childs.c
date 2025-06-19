/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:16:30 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 20:29:55 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static void	close_unused_pipes(int i, t_pipes *pipes)
{
	int	j;

	j = 0;
	while (j < pipes->pipes_count)
	{
		if (j != i - 1)
			close(pipes->pipefd[j][0]);
		if (j != i)
			close(pipes->pipefd[j][1]);
		j++;
	}
}

static int	process_child(int i, t_pipes *pipes, t_pipe_cmds *cmd_lst,
		t_data *data)
{
	int	exit_status;

	exit_status = 0;
	close_unused_pipes(i, pipes);
	if (save_fd_io(cmd_lst->cmd))
	{
		free_data_pipes(data, pipes);
		close_save_fd(data->ast);
		return (1);
	}
	if (dup_for_pipes(i, cmd_lst->cmd, pipes))
		return (close_save_fd(data->ast), 1);
	close_save_fd(data->ast);
	if (cmd_lst->cmd->cmd_line == NULL)
	{
		return (free_data_pipes(data, pipes), 0);
	}
	if (is_builtin(cmd_lst->cmd) == true)
	{
		signal(SIGPIPE, SIG_IGN);
		exit_status = exec_builtin(cmd_lst->cmd, data);
		free_data_pipes(data, pipes);
		return (exit_status);
	}
	else if (cmd_lst->cmd->type == CMD_LINE)
		exit_status = external_cmd_process(cmd_lst->cmd, data);
	// close_save_fd(data->ast);
	return (exit_status);
}

// backup_std_io(stdin_backup, stdout_backup);
// close_save_fd(data->ast);
// free_program(data);
// free_pipes_struct(pipes);

int	fork_and_exec_children(t_pipes *pipes, t_data *data)
{
	t_pipe_cmds	*tmp;
	int			i;
	int			exit_status;

	tmp = pipes->cmd_lst;
	i = -1;
	while (++i < pipes->process && tmp)
	{
		pipes->pid[i] = fork();
		if (pipes->pid[i] == -1)
			return (perror_free_pipes("Fork failed", pipes));
		if (pipes->pid[i] == 0)
		{
			set_signal_to_default();
			signal(SIGPIPE, SIG_DFL);
			exit_status = process_child(i, pipes, tmp, data);
			exit(exit_status);
		}
		set_signal_to_ignore();
		tmp = tmp->next;
	}
	return (0);
}
