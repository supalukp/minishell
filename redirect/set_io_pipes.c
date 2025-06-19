/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:31:48 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 19:02:33 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	setup_inout_first(t_pipes *pipes, t_tree *node)
{
	if (node->fd_in != -1)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (failed_dup(node->fd_in));
		close(node->fd_in);
		node->fd_in = -1;
	}
	if (node->fd_out != -1)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (failed_dup(node->fd_out));
		close(node->fd_out);
		node->fd_out = -1;
		close(pipes->pipefd[0][1]);
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
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (failed_dup(node->fd_in));
		close(node->fd_in);
		node->fd_in = -1;
		close(pipes->pipefd[i - 1][0]);
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
		node->fd_out = -1;
	}
	return (0);
}

static int	setup_middle_input(int i, t_pipes *pipes, t_tree *node)
{
	if (node->fd_in != -1)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (failed_dup(node->fd_in));
		close(node->fd_in);
		node->fd_in = -1;
		close(pipes->pipefd[i - 1][0]);
	}
	else
	{
		if (dup2(pipes->pipefd[i - 1][0], STDIN_FILENO) == -1)
			return (failed_dup(pipes->pipefd[i - 1][0]));
		close(pipes->pipefd[i - 1][0]);
	}
	return (0);
}

static int	setup_middle_output(int i, t_pipes *pipes, t_tree *node)
{
	if (node->fd_out != -1)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (failed_dup(node->fd_out));
		close(node->fd_out);
		node->fd_out = -1;
		close(pipes->pipefd[i][1]);
	}
	else
	{
		if (dup2(pipes->pipefd[i][1], STDOUT_FILENO) == -1)
			return (failed_dup(pipes->pipefd[i][1]));
		close(pipes->pipefd[i][1]);
	}
	return (0);
}

int	setup_inout_middle(int i, t_pipes *pipes, t_tree *node)
{
	int	error_flag;

	error_flag = setup_middle_input(i, pipes, node);
	if (error_flag)
		return (error_flag);
	error_flag = setup_middle_output(i, pipes, node);
	return (error_flag);
}

// static int	setup_inout_middle(int i, t_pipes *pipes, t_tree *node)
// {
// 	if (node->fd_in != -1)
// 	{
// 		if (dup2(node->fd_in, STDIN_FILENO) == -1)
// 			return (failed_dup(node->fd_in));
// 		close(node->fd_in);
// 		close(pipes->pipefd[i - 1][0]);
// 	}
// 	else
// 	{
// 		if (dup2(pipes->pipefd[i - 1][0], STDIN_FILENO) == -1)
// 			return (failed_dup(pipes->pipefd[i - 1][0]));
// 		close(pipes->pipefd[i - 1][0]);
// 	}
// 	if (node->fd_out != -1)
// 	{
// 		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
// 			return (failed_dup(node->fd_out));
// 		close(node->fd_out);
// 		close(pipes->pipefd[i][1]);
// 	}
// 	else
// 	{
// 		if (dup2(pipes->pipefd[i][1], STDOUT_FILENO) == -1)
// 			return (failed_dup(pipes->pipefd[i][1]));
// 		close(pipes->pipefd[i][1]);
// 	}
// 	return (0);
// }
