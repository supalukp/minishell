/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:06:42 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/14 15:07:24 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	close_unused_pipes(int i, t_pipes *pipes)
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

int	process_child(int i, t_pipes *pipes, t_pipe_cmds *cmd_lst, t_data *data)
{
	int	exit_status;

	exit_status = 0;
	set_signal_to_default();
	close_unused_pipes(i, pipes);
	setup_inout(i, pipes);
	if (redirect_io(cmd_lst->cmd, pipes, data) == -1)
	{
		return (1);
	}
	if (is_buildin(cmd_lst->cmd) == true)
	{
		exit_status = exec_buildin(cmd_lst->cmd, data);
		if (data)
			free_program(data);
	}
	else if (cmd_lst->cmd->type == CMD_LINE)
		exit_status = external_cmd_process(cmd_lst->cmd, data);
	return (exit_status);
}

// int	process_parent(t_pipes *pipes)
// {
// 	int	i;
// 	int	status;
// 	int	last_exit_status = 0;
// 	pid_t	last_pid = pipes->pid[pipes->process - 1]; // Track last command PID

// 	// Close all pipe fds
// 	for (i = 0; i < pipes->pipes_count; i++) {
// 		close(pipes->pipefd[i][0]);
// 		close(pipes->pipefd[i][1]);
// 	}

// 	// Wait for all children
// 	for (i = 0; i < pipes->process; i++) {
// 		pid_t pid = waitpid(pipes->pid[i], &status, 0);
// 		if (pid == -1)
// 			perror("waitpid");

// 		// Save the status of the last command
// 		if (pid == last_pid) {
// 			if (WIFEXITED(status))
// 				last_exit_status = WEXITSTATUS(status);
// 			else if (WIFSIGNALED(status)) {
// 				if (WTERMSIG(status) == SIGINT)
// 					write(1, "\n", 1);
// 				else if (WTERMSIG(status) == SIGQUIT)
// 					write(1, "Quit (core dumped)\n", 20);
// 				last_exit_status = 128 + WTERMSIG(status);
// 			}
// 		}
// 	}

// 	if (pipes)
// 		free_pipes_struct(pipes);
// 	return (last_exit_status);
// }


int	process_parent(t_pipes *pipes)
{
	int	i;
	int	status;
	int	last_exit_status;
	pid_t	last_pid;
	pid_t pid;


	i = -1;
	last_exit_status = 0;
	while (++i < pipes->pipes_count)
	{
		close(pipes->pipefd[i][0]);
		close(pipes->pipefd[i][1]);
	}
	i = -1;
	while (++i < pipes->process)
	{
		pid = waitpid(pipes->pid[i], &status, 0);
		if (pid == -1)
			perror("waitpid");
		last_pid = pipes->pid[pipes->process - 1];
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			else if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit (core dumped)\n", 20);
		}
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_exit_status = 128 + WTERMSIG(status);
		}
	}
	if (pipes)
		free_pipes_struct(pipes);
	return (last_exit_status);
}

static int	fork_and_exec_children(t_pipes *pipes, t_data *data)
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
			exit_status = process_child(i, pipes, tmp, data);
			free_pipes_struct(pipes);
			exit(exit_status);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	pipe_multi_process(t_tree *tree, t_data *data)
{
	t_pipes	*pipes;
	int		status;

	pipes = init_pipes(tree);
	if (!pipes)
		return (perror("malloc failed"), EXIT_FAILURE);
	create_pipes(pipes);
	if (fork_and_exec_children(pipes, data) != 0)
		return (EXIT_FAILURE);
	status = process_parent(pipes);
	return (status);
}
