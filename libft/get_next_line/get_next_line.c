/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:40:08 by spunyapr          #+#    #+#             */
/*   Updated: 2025/02/27 15:06:55 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_char(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	ft_st_bzero(char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
}

char	*get_buf(int fd, int *status, int i)
{
	ssize_t	char_read;
	char	*buf;
	char	*new_buf;
	char	*tmp;

	buf = NULL;
	while (i++ < 2 && buf == NULL)
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	char_read = read(fd, buf, BUFFER_SIZE);
	if (char_read <= 0)
	{
		if (char_read < 0)
			*status = -1;
		return (free(buf), NULL);
	}
	buf[char_read] = '\0';
	if (find_char(buf, '\n'))
		return (buf);
	new_buf = get_buf(fd, status, 0);
	if (!new_buf)
		return (buf);
	tmp = ft_strjoin(buf, new_buf);
	return (free(buf), free(new_buf), tmp);
}

char	*split_next_line(char *lines, char *buf, int i)
{
	char	*next_line;
	size_t	len_line;

	i = 0;
	if (lines && find_char(lines, '\n') == 0)
		return (lines);
	if (!lines || find_char(lines, '\n') == 0)
		return (NULL);
	len_line = 0;
	while (lines[len_line] != '\n' && lines[len_line] != '\0')
		len_line++;
	next_line = (char *)malloc(sizeof(char) * (len_line + 2));
	while (!next_line && i++ < 2)
		next_line = (char *)malloc(sizeof(char) * (len_line + 2));
	if (!next_line)
		return (NULL);
	ft_memcpy(next_line, lines, len_line);
	next_line[len_line] = '\n';
	next_line[len_line + 1] = '\0';
	if (lines[len_line] == '\n')
		len_line++;
	ft_memcpy(buf, lines + len_line, ft_strlen(lines) - len_line + 1);
	free(lines);
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	st_buf[BUFFER_SIZE + 1] = {0};
	char		*line;
	char		*tmp;
	int			status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	status = 0;
	if (find_char(st_buf, '\n') > 0)
	{
		tmp = ft_strdup(st_buf);
		ft_st_bzero(st_buf);
		return (split_next_line(tmp, st_buf, 0));
	}
	tmp = get_buf(fd, &status, 0);
	if (status == -1 || (!tmp && ft_strlen(st_buf) == 0))
		return (ft_st_bzero(st_buf), NULL);
	if (!tmp)
		line = ft_strdup(st_buf);
	else
		line = ft_strjoin(st_buf, tmp);
	if (!line)
		return (free(tmp), NULL);
	ft_st_bzero(st_buf);
	return (free(tmp), split_next_line(line, st_buf, 0));
}
