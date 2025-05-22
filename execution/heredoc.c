/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:18:31 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/22 17:26:18 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/headings.h"

int redirect_heredoc(char *delimiter)
{
    int fd_write;
    int fd_read;
    char *line;

    fd_write = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd_write == -1)
        return (1);
    line = get_next_line(0);
    if (!line)
        return (0);
    while (ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0)
    {
        if (ft_strncmp(line, delimiter, ft_strlen(line)) != 0)
            write(fd_write, line, ft_strlen(line));
        free(line);
        line = get_next_line(0);
        if (!line)
            break;
    }
    free(line);
    fd_read = open("/tmp/.heredoc_tmp", O_RDONLY);
    if (fd_read == -1)
        return (1);
    if (dup2(fd_read, STDIN_FILENO) == -1)
	{
		perror("dup2 failed for input redirection");
		close(fd_read);
		exit(EXIT_FAILURE);
	}
    close(fd_read);
    unlink("/tmp/.heredoc_tmp");
    return (0);
}
