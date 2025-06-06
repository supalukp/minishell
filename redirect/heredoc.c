/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:18:31 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/06 15:28:27 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	heredoc_get_line(char *delimiter, int fd_tty, int fd_write)
{
	char	*line;

	while (1)
	{
		write(fd_tty, "> ", 2);
		line = get_next_line(fd_tty);
		if (!line)
			break ;
		if (ft_strlen(line) == ft_strlen(delimiter) + 1 && ft_strncmp(line,
				delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd_write, line, ft_strlen(line));
		free(line);
	}
	close(fd_tty);
	close(fd_write);
}

int	read_tmp_file(char *tmpfile)
{
	int	fd_read;

	fd_read = open(tmpfile, O_RDONLY);
	if (fd_read == -1)
		return (-1);
	if (dup2(fd_read, STDIN_FILENO) == -1)
	{
		perror("dup2 failed for heredoc input");
		close(fd_read);
		return (EXIT_FAILURE);
	}
	close(fd_read);
	return (0);
}

int	redirect_heredoc(char *delimiter)
{
	int		fd_write;
	int		fd_tty;
	char	*tmpfile;

	tmpfile = create_random_filename();
	fd_write = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd_write == -1)
		return (-1);
	fd_tty = open("/dev/tty", O_RDWR);
	if (fd_tty == -1)
	{
		perror("open /dev/tty failed");
		close(fd_write);
		return (-1);
	}
	heredoc_get_line(delimiter, fd_tty, fd_write);
	if (read_tmp_file(tmpfile) != 0)
		return (-1);
	unlink(tmpfile);
	free(tmpfile);
	return (0);
}

char	*create_random_filename(void)
{
	int		fd_tmp;
	int		i;
	char	*alnum;
	char	rand_bytes[8];
	char	*tmp_file;
	char	*filename;

	tmp_file = malloc(sizeof(char) * 9);
	alnum = ft_strdup("abcdefghijklmnopqrstuvwxyz0123456789");
	fd_tmp = open("/dev/random", O_RDONLY);
	if (!fd_tmp)
		return (NULL);
	read(fd_tmp, rand_bytes, 8);
	i = 0;
	while (i < 8)
	{
		tmp_file[i] = alnum[rand_bytes[i] % ft_strlen(alnum)];
		i++;
	}
	tmp_file[i] = '\0';
	close(fd_tmp);
	free(alnum);
	filename = ft_strjoin("/tmp/.heredoc_", tmp_file);
	free(tmp_file);
	return (filename);
}
