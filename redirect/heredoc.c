/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:18:31 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/16 17:01:15 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	heredoc_get_line(char *delimiter, int fd_tty, int fd_write)
{
	char	*line;

	while (1)
	{
		write(fd_tty, "> ", 2);
		line = get_next_line(fd_tty);
		if (g_signal == SIGINT || !line)
			break ;
		if (ft_strlen(line) == ft_strlen(delimiter) + 1 && !ft_strncmp(line,
				delimiter, ft_strlen(delimiter))
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		free(line);
	}
	if (g_signal == SIGINT)
		return (close(fd_tty), close(fd_write), 130);
	close(fd_tty);
	close(fd_write);
	return (0);
}

int	redirect_heredoc(t_file *file, t_tree *node)
{
	int		fd_write;
	int		fd_tty;
	int		fd_read;
	int		status;
	char	*tmpfile;

	g_signal = 0;
	setup_heredoc_signal();
	fd_write = open_tmpfile(&tmpfile);
	if (fd_write == -1)
		return (1);
	fd_tty = open_tty(tmpfile, fd_write);
	if (fd_tty == -1)
		return (1);
	status = heredoc_get_line(file->content, fd_tty, fd_write);
	if (status == 130)
		return (clean_exit(tmpfile, fd_write, fd_tty, 130));
	fd_read = open(tmpfile, O_RDONLY);
	if (fd_read == -1)
		return (handle_heredoc_open_fail(tmpfile));
	assign_heredoc_fd(node, fd_read);
	unlink(tmpfile);
	free(tmpfile);
	set_signal_to_default();
	return (0);
}
