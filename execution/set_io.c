/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:47:08 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/18 17:30:20 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

// if this function return (-1 I have to free_all_exit(data, pipes));
int	save_fd_io(t_tree *node)
{
	t_file	*files;
	int		new_fd_in;
	int		new_fd_out;

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

