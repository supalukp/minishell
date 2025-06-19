/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:18:31 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 09:26:40 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

/*
	int	set_all_heredoc(t_tree *node);

	Heredoc step:
	1. create_random_filename() for temporary file name by get 8 bytes from
		/dev/random and convert it to alphanum
	2. redirect_heredoc
		function will return set tree->fd_heredoc = fd that return from open()
		when we try to read from tmp file
		[x] set up signal for heredoc
		[x] create random tmp filename
		[x] open fd_write for writing input in the tmpfile
		[x] open fd_tty to make sure that we read directly from terminal
		[x] get_heredoc_line : get input line by line and write to
		tmp file (fd_write)
		[x] after user type the delimiter the get line stop and close(fd_write)
		and close(fd_tty)
		[x] also in heredoc_get_line we listen the signal if get sigint(ctrl+c)
		we close fd and return 130
		[x] if heredoc_get_line return 130 unlink(tmpfile) free(tmpfile)
		and set signal to default
		[] read tmpfile fd_read = open(tmpfile, O_RDONLY);
			if (fd_read != -1) set tree->fd_heredoc == fd_read
				-> unlink(tmpfile) free(tmpfile) set_signal_to_default
			***if we have more than one << heredoc
			-> check if tree->fd_heredoc != STDIN_FILENO
						close(tree->fd_heredoc);
					tree->fd_heredoc = fd_read (new one)

	NOTE:
	- if heredoc get interrupt by signal like sigint the whole line of
	command return 130
	- Suggestion: validate fd_read >= 0 instead of fd_read != -1 for clarity
	- If multiple heredocs are in a single command,
		and SIGINT happens in the first one: Clean up all opened fd_heredoc
		from other nodes if already opened
	- Make sure after dup2
		if (node->fd_heredoc != -1)
		{
			close(node->fd_heredoc);
			node->fd_heredoc = -1;
		}
	- int get_heredoc(char *delimiter)
		{
			if (get_line == 130)
				return (130) for signal --> also tell main that
				if get_heredoc == 130
					-> exit_status == 130 and don't go to execution
			int fd_read = open(tmpfile, O_RDONLY);
			if (fd_read == -1)
			{
				perror("heredoc open failed");
				return (-1);  --> if cannot read
			}
			return (fd_read);
		}
*/

static int	read_random_bytes(char *buffer, int size)
{
	int	fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0 || read(fd, buffer, size) < 0)
	{
		if (fd >= 0)
			close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static char	*generate_tmp_name(char *rand_bytes)
{
	int		i;
	char	*alnum;
	char	*tmp;

	alnum = ft_strdup("abcdefghijklmnopqrstuvwxyz0123456789");
	if (!alnum)
		return (NULL);
	tmp = malloc(sizeof(char) * 9);
	if (!tmp)
		return (free(alnum), NULL);
	i = -1;
	while (++i < 8)
		tmp[i] = alnum[(unsigned char)rand_bytes[i] % ft_strlen(alnum)];
	tmp[8] = '\0';
	free(alnum);
	return (tmp);
}

static char	*create_random_filename(void)
{
	char	rand_bytes[8];
	char	*tmp_file;
	char	*filename;

	if (read_random_bytes(rand_bytes, 8))
		return (NULL);
	tmp_file = generate_tmp_name(rand_bytes);
	if (!tmp_file)
		return (NULL);
	filename = ft_strjoin("/tmp/.heredoc_", tmp_file);
	free(tmp_file);
	return (filename);
}

// static char	*create_random_filename(void)
// {
// 	int		fd_tmp;
// 	int		i;
// 	char	*alnum;
// 	char	rand_bytes[8];
// 	char	*tmp_file;
// 	char	*filename;

// 	tmp_file = malloc(sizeof(char) * 9);
// 	alnum = ft_strdup("abcdefghijklmnopqrstuvwxyz0123456789");
// 	fd_tmp = open("/dev/random", O_RDONLY);
// 	if (!fd_tmp)
// 	{
// 		free(tmp_file);
// 		free(alnum);
// 		return (NULL);
// 	}
// 	read(fd_tmp, rand_bytes, 8);
// 	i = 0;
// 	while (i < 8)
// 	{
// 		tmp_file[i] = alnum[rand_bytes[i] % ft_strlen(alnum)];
// 		i++;
// 	}
// 	tmp_file[i] = '\0';
// 	close(fd_tmp);
// 	free(alnum);
// 	filename = ft_strjoin("/tmp/.heredoc_", tmp_file);
// 	free(tmp_file);
// 	return (filename);
// }

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

// static int	heredoc_get_line(char *delimiter, int fd_tty, int fd_write)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		write(fd_tty, "> ", 2);
// 		line = get_next_line(fd_tty);
// 		if (g_signal == SIGINT)
// 		{
// 			close(fd_tty);
// 			close(fd_write);
// 			return (130);
// 		}
// 		if (!line)
// 			break ;
// 		if (ft_strlen(line) == ft_strlen(delimiter) + 1 && ft_strncmp(line,
// 				delimiter, ft_strlen(delimiter)) == 0
// 			&& line[ft_strlen(delimiter)] == '\n')
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(fd_write, line, ft_strlen(line));
// 		free(line);
// 	}
// 	close(fd_tty);
// 	close(fd_write);
// 	return (0);
// }

static int	clean_exit(char *tmpfile, int fd_write, int fd_tty, int ret)
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

static int	open_tmpfile(char **tmpfile)
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

static int	open_tty(char *tmpfile, int fd_write)
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

static int	handle_heredoc_open_fail(char *tmpfile)
{
	perror("heredoc open failed");
	return (clean_exit(tmpfile, -1, -1, 1));
}

static void	assign_heredoc_fd(t_tree *node, int fd_read)
{
	if (node->fd_heredoc != -1)
		close(node->fd_heredoc);
	node->fd_heredoc = fd_read;
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

// int	redirect_heredoc(t_file *file, t_tree *node)
// {
// 	int		fd_write;
// 	int		fd_tty;
// 	int		fd_read;
// 	char	*tmpfile;
// 	int		status;

// 	g_signal = 0;
// 	setup_heredoc_signal();
// 	tmpfile = create_random_filename();
// 	fd_write = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
// 	if (fd_write == -1)
// 	{
// 		perror("open tmpfile for writing failed");
// 		free(tmpfile);
// 		return (1);
// 	}
// 	fd_tty = open("/dev/tty", O_RDWR);
// 	if (fd_tty == -1)
// 	{
// 		perror("open /dev/tty failed");
// 		return (clean_exit(tmpfile, fd_write, -1, 1));
// 	}
// 	status = heredoc_get_line(file->content, fd_tty, fd_write);
// 	if (status == 130)
// 		return (clean_exit(tmpfile, fd_write, fd_tty, 130));
// 	fd_read = open(tmpfile, O_RDONLY);
// 	if (fd_read == -1)
// 	{
// 		perror("heredoc open failed");
// 		return (clean_exit(tmpfile, -1, -1, 1));
// 	}
// 	if (node->fd_heredoc != -1)
// 		close(node->fd_heredoc);
// 	node->fd_heredoc = fd_read;
// 	unlink(tmpfile);
// 	free(tmpfile);
// 	set_signal_to_default();
// 	return (0);
// }
