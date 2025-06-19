/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:29:18 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/18 17:29:38 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	safe_close(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	close_save_fd(t_tree *node)
{
	safe_close(&node->fd_in);
	safe_close(&node->fd_out);
	safe_close(&node->fd_heredoc);
}

int	failed_dup(int fd)
{
	perror("dup2 failed");
	close(fd);
	return (1);
}
