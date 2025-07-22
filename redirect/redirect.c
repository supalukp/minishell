/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:46:44 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 13:13:18 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

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
	close_save_fd(node);
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
