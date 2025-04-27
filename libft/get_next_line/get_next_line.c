/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:52:49 by syukna            #+#    #+#             */
/*   Updated: 2025/01/27 15:22:25 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	includedchar(char const *buffer, char c)
{
	while (*buffer && *buffer != '\0')
	{
		if (c == *buffer)
			return (1);
		buffer++;
	}
	return (0);
}

static void	shift_buffer(char *buffer)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = 0;
	while (buffer[start] && buffer[start] != '\n')
		start++;
	if (buffer[start] == '\n')
		start++;
	while (buffer[start])
		buffer[i++] = buffer[start++];
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
}

char	*get_current_line(char *line, char *buffer)
{
	size_t	i;
	size_t	len;
	size_t	new_len;
	char	*new_line;

	i = 0;
	len = ft_strlen(line);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	new_len = len + i;
	new_line = ft_calloc(new_len + 1, sizeof(char));
	if (!new_line)
		return (free(line), NULL);
	ft_strlcpy(new_line, line, len + 1);
	ft_strlcpy(&new_line[len], buffer, i + 1);
	return (free(line), new_line);
}

static char	*read_line(char *line, char *buffer, int fd)
{
	ssize_t		bytes_read;

	bytes_read = 1;
	while (bytes_read != 0 && !includedchar(buffer, '\n'))
	{
		line = get_current_line(line, buffer);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(line), ft_bzero(buffer, BUFFER_SIZE), NULL);
		if (bytes_read == 0)
		{
			ft_bzero(buffer, BUFFER_SIZE);
			if (*line)
				return (line);
			free (line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
	}
	line = get_current_line(line, buffer);
	shift_buffer(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_calloc(1, sizeof(char));
	if (!line)
		return (NULL);
	line = read_line(line, buffer[fd], fd);
	return (line);
}
