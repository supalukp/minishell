/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tmp_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:23:15 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 13:12:07 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

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

char	*create_random_filename(void)
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
