/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:29:18 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 17:13:52 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static void	safe_close(int *fd)
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
