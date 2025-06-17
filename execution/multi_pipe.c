/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:06:42 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/17 16:35:29 by spunyapr         ###   ########.fr       */
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

/*
	Redirection plan:

	[x]	0. Save heredoc fd before come to execution	
	[x]	1. save_fd_io(); Loop though t_file to open all files and save only last io in tree->fd_in / tree->fd_out 
	- Open and save fd + check if fd_in != -1 -> tree->fd_in = open(infile...);
	- Close fd_before
	- if (file->type == HEREDOC) get fd from tree->fd_heredoc and close after (Maybe double check with close_all_heredoc_fd();)
	[]	2. call function dup_fd_io() -> seperate : one_cmd and pipe 
	- for one cmd -> cd tree->fd_in and tree->fd_out if != -1 dup this and close it
	- for pipes -> do like setup_inout() but also check like if (tree->fd_in != -1) dup2(fd_in, STDIN_FIRENO) -> else maybe from  pipes if it is middle one

*/

int	get_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	// if (dup2(fd, STDIN_FILENO) == -1)
	// {
	// 	perror("dup2 failed for input redirection");
	// 	close(fd);
	// 	return (-1);
	// }
	// close(fd);
	return (fd);
}

int	get_outfile(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	return (fd);
}

int	get_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	return (fd);
}

void safe_close(int *fd)
{
    if (*fd != -1)
    {
        close(*fd);
        *fd = -1;
    }
}

void close_save_fd(t_tree *node)
{
    safe_close(&node->fd_in);
    safe_close(&node->fd_out);
    safe_close(&node->fd_heredoc);
}

// if this function return -1 I have to free_all_exit(data, pipes);
int save_fd_io(t_tree *node)
{
	t_file *files;
	int new_fd_in;
	int new_fd_out;

	files = node->files;
	while (files)
	{
		if (files->type == INFILE)
		{
			new_fd_in = get_infile(files->content);
			if (new_fd_in == -1)
			{
				close_save_fd(node);
				return (1);
			}
			else if (node->fd_in != -1)
				close(node->fd_in);
			node->fd_in = new_fd_in;
		}
		else if (files->type == HEREDOC)
		{
			new_fd_in = node->fd_heredoc;
			if (node->fd_in != -1)
				close(node->fd_in);
			node->fd_in = new_fd_in;
		}
		else if (files->type == OUTFILE)
		{
			new_fd_out = get_outfile(files->content);
			if (new_fd_out == -1)
			{
				close_save_fd(node);
				return (1);
			}
			else if (node->fd_out != -1)
				close(node->fd_out);
			node->fd_out = new_fd_out;
		}
		else if (files->type == APPEND)
		{
			new_fd_out = get_append(files->content);
			if (new_fd_out == -1)
			{
				close_save_fd(node);
				return (1);
			}
			else if (node->fd_out != -1)
				close(node->fd_out);
			node->fd_out = new_fd_out;
		}
		else
		{
			close_save_fd(node);
			return (1);
		}
		files = files->next;
	}
	return (0);
}


int failed_dup(int fd)
{
	perror("dup2 failed");
	close(fd);
	return (1);
}

int	setup_inout_first(t_pipes *pipes, t_tree *node)
{
	if (node->fd_in != -1)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (failed_dup(node->fd_in));
		close(node->fd_in);
	}
	if (node->fd_out != -1)
	{
		close(pipes->pipefd[0][1]);
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (failed_dup(node->fd_out));
		close(node->fd_out);
	}
	else
	{
		if (dup2(pipes->pipefd[0][1], STDOUT_FILENO) == -1)
			return (failed_dup(pipes->pipefd[0][1]));
		close(pipes->pipefd[0][1]);
	}
	return (0);
}

int	setup_inout_last(int i, t_pipes *pipes, t_tree *node)
{
	if (node->fd_in != -1)
	{
		close(pipes->pipefd[i - 1][0]);
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (failed_dup(node->fd_in));
		close(node->fd_in);
	}
	else
	{
		if (dup2(pipes->pipefd[i - 1][0], STDIN_FILENO) == -1)
			return (failed_dup(pipes->pipefd[i - 1][0]));
		close(pipes->pipefd[i - 1][0]);
	}
	if (node->fd_out != -1)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (failed_dup(node->fd_out));
		close(node->fd_out);
	}
	return (0);
}


int	setup_inout_middle(int i, t_pipes *pipes, t_tree *node)
{
	if (node->fd_in != -1)
	{
		close(pipes->pipefd[i - 1][0]);
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (failed_dup(node->fd_in));
		close(node->fd_in);
	}
	else
	{
		if (dup2(pipes->pipefd[i - 1][0], STDIN_FILENO) == -1)
			return (failed_dup(pipes->pipefd[i - 1][0]));
		close(pipes->pipefd[i - 1][0]);
	}
	if (node->fd_out != -1)
	{
		close(pipes->pipefd[i][1]);
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (failed_dup(node->fd_out));
		close(node->fd_out);
	}
	else
	{
		if (dup2(pipes->pipefd[i][1], STDOUT_FILENO) == -1)
			return (failed_dup(pipes->pipefd[i][1]));
		close(pipes->pipefd[i][1]);
	}
	return (0);
}

int dup_for_pipes(int i, t_tree *node, t_pipes *pipes)
{
	int ret;

	if (pipes->pipes_count == 0)
		return (0);
	if (i == 0)
		ret = setup_inout_first(pipes, node);
	else if (i == pipes->process - 1)
		ret = setup_inout_last(i, pipes, node);
	else
		ret = setup_inout_middle(i, pipes, node);
	if (ret)
		return (1);
	return (0);
}

int dup_for_one_cmd(t_tree *node)
{
	if (node->fd_in != -1)
	{
		printf("dup fd_in\n");
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (failed_dup(node->fd_in));
		close(node->fd_in);
	}
	if (node->fd_out != -1)
	{
		printf("dup fd_out\n");
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (failed_dup(node->fd_out));
		close(node->fd_out);
	}
	return (0);
}

int	process_child(int i, t_pipes *pipes, t_pipe_cmds *cmd_lst, t_data *data)
{
	int	exit_status;

	exit_status = 0;
	close_unused_pipes(i, pipes); // OK
	// setup_inout(i, pipes); // Merge with redirect
	// if (redirect_io(cmd_lst->cmd, pipes, data) == -1)
	// {
	// 	return (1);
	// }
	if (save_fd_io(cmd_lst->cmd))
	{
		free_all_exit(data, pipes);
		return (1);
	}
	if (dup_for_pipes(i, cmd_lst->cmd, pipes))
		return (1);
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
			set_signal_to_default();
			exit_status = process_child(i, pipes, tmp, data);
			free_pipes_struct(pipes);
			exit(exit_status);
		}
		set_signal_to_ignore();
		tmp = tmp->next;
	}
	return (0);
}

// void prepare_heredoc(t_pipe_cmds *lst)
// {
// 	while (lst)
// 	{
// 		while (lst->cmd->files)
// 		{
// 			if (lst->cmd->files == HEREDOC)
// 				lst->fd_in = redirect_heredoc(lst->cmd->files->content);
// 			lst->cmd->files = lst->cmd->files->next;
// 		}
// 		lst = lst->next;
// 	}
// }

int	pipe_multi_process(t_tree *tree, t_data *data)
{
	t_pipes	*pipes;
	int		status;
	int		stdin_backup;
	int		stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	pipes = init_pipes(tree);
	if (!pipes)
		return (perror("malloc failed"), EXIT_FAILURE);
	create_pipes(pipes);
	if (fork_and_exec_children(pipes, data) != 0)
	{
		backup_std_io(stdin_backup, stdout_backup);
		return (EXIT_FAILURE);
	}
	status = process_parent(pipes);
	backup_std_io(stdin_backup, stdout_backup);
	return (status);
}
