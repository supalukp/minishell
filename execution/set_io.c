/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:47:08 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/16 13:45:38 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	handle_infile(t_tree *node, t_file *file)
{
	int	fd;

	fd = get_infile(file->content);
	if (fd == -1)
		return (close_save_fd(node), 1);
	if (node->fd_in != -1)
		close(node->fd_in);
	node->fd_in = fd;
	return (0);
}

static int	handle_outfile(t_tree *node, t_file *file)
{
	int	fd;

	fd = get_outfile(file->content);
	if (fd == -1)
		return (close_save_fd(node), 1);
	if (node->fd_out != -1)
		close(node->fd_out);
	node->fd_out = fd;
	return (0);
}

static int	handle_append(t_tree *node, t_file *file)
{
	int	fd;

	fd = get_append(file->content);
	if (fd == -1)
		return (close_save_fd(node), 1);
	if (node->fd_out != -1)
		close(node->fd_out);
	node->fd_out = fd;
	return (0);
}

int	save_fd_io(t_tree *node)
{
	t_file	*files;

	files = node->files;
	while (files)
	{
		if (files->type == INFILE && handle_infile(node, files))
			return (1);
		else if (files->type == HEREDOC)
		{
			if (node->fd_in != -1)
				close(node->fd_in);
			node->fd_in = node->fd_heredoc;
			node->fd_heredoc = -1;
		}
		else if (files->type == OUTFILE && handle_outfile(node, files))
			return (1);
		else if (files->type == APPEND && handle_append(node, files))
			return (1);
		else if (files->type != INFILE && files->type != HEREDOC
			&& files->type != OUTFILE && files->type != APPEND)
			return (close_save_fd(node), 1);
		files = files->next;
	}
	return (0);
}
