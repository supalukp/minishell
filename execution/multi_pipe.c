/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:06:42 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/14 16:23:24 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	count_pipes(t_tree_token *tree)
{
	t_tree_token	*token;
	int				count;

	token = tree;
	count = 0;
	while (token->type == PIPE)
	{
		count++;
		token = token->left;
	}
	return (count);
}

int	create_pipe(int **pipefd, int i)
{
	if (pipe(pipefd[i][2] == -1))
		return (perror("pipe failed"), EXIT_FAILURE);
}

void	close_unused_pipes(int *pipefd[2], int pipe_count, int i)
{
	int	j;

	j = 0;
	while (j < pipe_count)
	{
		if (j != i - 1)
			close(pipefd[j][0]);
		if (j != i)
			close(pipefd[j][1]);
		j++;
	}
}

void	setup_inout_first(int **pipefd, int pipe_count)
{
	int	fd_in;

	// if redirect();
	fd_in = open(pipex->argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		close(pipex->fd[0][1]);
		// free_double_array(pipex->fd);
		// free(pipex->pid);
		return (perror("open files failed"), EXIT_FAILURE);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(pipefd[0][1], STDOUT_FILENO);
	close(pipefd[0][1]);
}

void	setup_inout_last(int **pipefd, int pipe_count)
{
	int	i;
	int	fd_out;

	i = pipe_count - 1;
	close(pipefd[i][1]);
	fd_out = open(pipex->argv[pipex->argc - 1], O_CREAT | O_WRONLY | O_TRUNC,
			0644);
	if (pipex->fd_out == -1)
	{
		close(pipefd[i - 1][0]);
		// free_double_array(pipex->fd);
		// free(pipex->pid);
		return (perror("open files failed"), EXIT_FAILURE);
	}
	dup2(pipefd[i - 1][0], STDIN_FILENO);
	close(pipefd[i - 1][0]);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	setup_inout(int i, int **pipefd, int pipe_count)
{
	if (i == 0)
		setup_inout_first(pipex);
	else if (i == pipe_count - 1)
		setup_inout_last(pipex);
	else
	{
		dup2(pipefd[i - 1][0], STDIN_FILENO);
		close(pipefd[i - 1][0]);
		dup2(pipefdfd[i][1], STDOUT_FILENO);
		close(pipefd[i][1]);
		// redirect in out
	}
}

int	**create_double_fd(int process_num)
{
	int	i;
	int	**fd;

	fd = (int **)malloc(sizeof(int *) * (process_num + 1));
	if (!fd)
		return (NULL);
	i = 0;
	while (i < process_num)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			free_double_array(fd);
			return (NULL);
		}
		i++;
	}
	fd[process_num] = NULL;
	return (fd);
}

void	process_child(int i, int **pipefd, int pipe_count)
{
	close_unused_pipesclose_unused_pipes(pipefd, pipe_count, i);
	setup_inout(i, pipefd, pipe_count);
	execute_command(pipex->argv[i + 2], pipex);
}

int	pipe_multi_process(t_tree_token *tree, t_data *data)
{
	int		*pipefd[2];
	pid_t	*pid;
	int		pipe_count;
	int		i;

	pipe_count = count_pipes(tree);
	pipefd = create_double_fd(pipe_count + 1);
	if (!pipefd)
		return (perror("malloc failed"), EXIT_FAILURE);
	pid = malloc(sizeof(pid_t) * (pipe_count + 1));
	if (!pid)
		return (perror("malloc failed"), EXIT_FAILURE);
	// 1. Loop check left to go to the first cmd that should execute first
		&& Create pipes
	i = 0;
	while (tree->type == PIPE)
	{
		create_pipe(pipefd, i); // TODO
		tree = tree->left;
		i++;
	}
	i = 0;
	while (i < count_pipes + 1)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (perror("Fork failed"), EXIT_FAILURE);
		if (pid[i] == 0)
			process_child(i, )
	}
	// 2. Fork process on first pipes
	// 3.   Child 1 = Left cmd
	// 3.1 go through infile list / outfiles list (Open + Redirect)
	// 3.2 Execve
	// 4. Wait and get exit_status of the right one
}
