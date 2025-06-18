/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:46:44 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/18 18:21:40 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

/*
	Redirection plan:

	[x]	0. Save heredoc fd before come to execution
	[x]	1. save_fd_io(); Loop though t_file to open all files and save only last io in tree->fd_in
			/ tree->fd_out
	- Open and save fd + check if fd_in != -1 -> tree->fd_in = open(infile...);
	- Close fd_before
	- if (file->type == HEREDOC) get fd from tree->fd_heredoc and close after (Maybe double check with close_all_heredoc_fd();)
	[]	2. call function dup_fd_io() -> seperate : one_cmd and pipe
	- for one cmd -> cd tree->fd_in and tree->fd_out if !=
		-1 dup this and close it
	- for pipes -> do like setup_inout() but also check like if (tree->fd_in !=
		-1) dup2(fd_in, STDIN_FIRENO)
		-> else maybe from  pipes if it is middle one

*/

static int	setup_inout_first(t_pipes *pipes, t_tree *node)
{
	if (node->fd_in != -1)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
		{
			printf("1\n");
			return (failed_dup(node->fd_in));
		}
		close(node->fd_in);
	}
	if (node->fd_out != -1)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
		{
			printf("2\n");
			return (failed_dup(node->fd_out));
		}
		close(node->fd_out);
		close(pipes->pipefd[0][1]);
	}
	else
	{
		if (dup2(pipes->pipefd[0][1], STDOUT_FILENO) == -1)
		{
			printf("3\n");
			return (failed_dup(pipes->pipefd[0][1]));
		}
		close(pipes->pipefd[0][1]);
	}
	return (0);
}

static int	setup_inout_last(int i, t_pipes *pipes, t_tree *node)
{
	if (node->fd_in != -1)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
		{
			printf("4\n");
			return (failed_dup(node->fd_in));
		}
		close(node->fd_in);
		close(pipes->pipefd[i - 1][0]);
	}
	else
	{
		if (dup2(pipes->pipefd[i - 1][0], STDIN_FILENO) == -1)
		{
			printf("5\n");
			return (failed_dup(pipes->pipefd[i - 1][0]));
		}
		close(pipes->pipefd[i - 1][0]);
	}
	if (node->fd_out != -1)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
		{
			printf("6\n");
			return (failed_dup(node->fd_out));
		}
		close(node->fd_out);
	}
	return (0);
}

static int	setup_inout_middle(int i, t_pipes *pipes, t_tree *node)
{
	if (node->fd_in != -1)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
		{
			printf("7\n");
			return (failed_dup(node->fd_in));
		}
		close(node->fd_in);
		close(pipes->pipefd[i - 1][0]);
	}
	else
	{
		if (dup2(pipes->pipefd[i - 1][0], STDIN_FILENO) == -1)
		{
			printf("8\n");
			return (failed_dup(pipes->pipefd[i - 1][0]));
		}
		close(pipes->pipefd[i - 1][0]);
	}
	if (node->fd_out != -1)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
		{
			printf("9\n");
			return (failed_dup(node->fd_out));
		}
		close(node->fd_out);
		close(pipes->pipefd[i][1]);
	}
	else
	{
		if (dup2(pipes->pipefd[i][1], STDOUT_FILENO) == -1)
		{
			printf("10\n");
			return (failed_dup(pipes->pipefd[i][1]));
		}
		close(pipes->pipefd[i][1]);
	}
	return (0);
}

int	dup_for_pipes(int i, t_tree *node, t_pipes *pipes)
{
	int	ret;

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

int	dup_for_one_cmd(t_tree *node)
{
	if (node->fd_in != -1)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (failed_dup(node->fd_in));
		close(node->fd_in);
	}
	if (node->fd_out != -1)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (failed_dup(node->fd_out));
		close(node->fd_out);
	}
	return (0);
}
