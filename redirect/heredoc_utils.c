/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:25:20 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 11:35:13 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	open_tmpfile(char **tmpfile)
{
	int	fd;

	*tmpfile = create_random_filename();
	fd = open(*tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("open tmpfile for writing failed");
		free(*tmpfile);
	}
	return (fd);
}

int	open_tty(char *tmpfile, int fd_write)
{
	int	fd_tty;

	fd_tty = open("/dev/tty", O_RDWR);
	if (fd_tty == -1)
	{
		perror("open /dev/tty failed");
		clean_exit(tmpfile, fd_write, -1, 1);
	}
	return (fd_tty);
}

int	handle_heredoc_open_fail(char *tmpfile)
{
	perror("heredoc open failed");
	return (clean_exit(tmpfile, -1, -1, 1));
}

int	clean_exit(char *tmpfile, int fd_write, int fd_tty, int ret)
{
	if (fd_write != -1)
		close(fd_write);
	if (fd_tty != -1)
		close(fd_tty);
	if (tmpfile)
	{
		unlink(tmpfile);
		free(tmpfile);
	}
	set_signal_to_default();
	return (ret);
}

void	assign_heredoc_fd(t_tree *node, int fd_read)
{
	if (node->fd_heredoc != -1)
		close(node->fd_heredoc);
	node->fd_heredoc = fd_read;
}
