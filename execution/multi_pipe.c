/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:06:42 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 00:13:23 by spunyapr         ###   ########.fr       */
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
		return (1);
	}
	if (dup_for_pipes(i, cmd_lst->cmd, pipes))
		return (1);
	close_save_fd(data->ast);
	if (cmd_lst->cmd->cmd_line == NULL)
		return (0);
	if (is_buildin(cmd_lst->cmd) == true)
	{
		signal(SIGPIPE, SIG_IGN);
		exit_status = exec_buildin(cmd_lst->cmd, data);
		free_program(data);
		free_pipes_struct(pipes);
		return (exit_status);
	}
	else if (cmd_lst->cmd->type == CMD_LINE)
		exit_status = external_cmd_process(cmd_lst->cmd, data);
	return (exit_status);
}

static void	close_all_pipes(t_pipes *pipes)
{
	int	i;

	i = -1;
	while (++i < pipes->pipes_count)
	{
		close(pipes->pipefd[i][0]);
		close(pipes->pipefd[i][1]);
	}
}

static void	handle_signal_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 20);
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
	int		last_exit_status;
	pid_t	pid;
	pid_t	last_pid;

	i = 0;
	last_exit_status = 0;
	last_pid = pipes->pid[pipes->process - 1];
	while (i < pipes->process)
	{
		pid = waitpid(pipes->pid[i], &status, 0);
		if (pid == -1)
			perror("waitpid");
		handle_signal_status(status);
		update_exit_status(pid, last_pid, status, &last_exit_status);
		i++;
	}
	return (last_exit_status);
}

static int	process_parent(t_pipes *pipes)
{
	int	last_exit_status;

	close_all_pipes(pipes);
	last_exit_status = wait_for_children(pipes);
	free_pipes_struct(pipes);
	return (last_exit_status);
}

// static int	process_parent(t_pipes *pipes)
// {
// 	int		i;
// 	int		status;
// 	int		last_exit_status;
// 	pid_t	last_pid;
// 	pid_t	pid;

// 	i = -1;
// 	last_exit_status = 0;
// 	while (++i < pipes->pipes_count)
// 	{
// 		close(pipes->pipefd[i][0]);
// 		close(pipes->pipefd[i][1]);
// 	}
// 	i = -1;
// 	while (++i < pipes->process)
// 	{
// 		pid = waitpid(pipes->pid[i], &status, 0);
// 		if (pid == -1)
// 			perror("waitpid");
// 		last_pid = pipes->pid[pipes->process - 1];
// 		if (WIFSIGNALED(status))
// 		{
// 			if (WTERMSIG(status) == SIGINT)
// 				write(1, "\n", 1);
// 			else if (WTERMSIG(status) == SIGQUIT)
// 				write(1, "Quit (core dumped)\n", 20);
// 		}
// 		if (pid == last_pid)
// 		{
// 			if (WIFEXITED(status))
// 				last_exit_status = WEXITSTATUS(status);
// 			else if (WIFSIGNALED(status))
// 				last_exit_status = 128 + WTERMSIG(status);
// 		}
// 	}
// 	if (pipes)
// 		free_pipes_struct(pipes);
// 	return (last_exit_status);
// }

// backup_std_io(stdin_backup, stdout_backup);
// close_save_fd(data->ast);
// free_program(data);
// free_pipes_struct(pipes);

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

int	pipe_multi_process(t_tree *tree, t_data *data)
{
	t_pipes	*pipes;
	int		status;

	pipes = init_pipes(tree);
	if (!pipes)
		return (perror("malloc failed"), EXIT_FAILURE);
	create_pipes(pipes);
	if (fork_and_exec_children(pipes, data) != 0)
	{
		close_save_fd(data->ast);
		return (EXIT_FAILURE);
	}
	status = process_parent(pipes);
	close_save_fd(data->ast);
	return (status);
}
