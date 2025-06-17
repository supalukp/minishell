/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:47:08 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/17 14:31:00 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

// void	setup_inout_first(t_pipes *pipes)
// {
// 	dup2(pipes->pipefd[0][1], STDOUT_FILENO);
// 	close(pipes->pipefd[0][1]);
// }

// void	setup_inout_last(t_pipes *pipes)
// {
// 	int	i;

// 	i = pipes->process - 1;
// 	dup2(pipes->pipefd[i - 1][0], STDIN_FILENO);
// 	close(pipes->pipefd[i - 1][0]);
// }

// void	setup_inout(int i, t_pipes *pipes)
// {
// 	if (pipes->pipes_count == 0)
// 		return ;
// 	if (i == 0)
// 		setup_inout_first(pipes);
// 	else if (i == pipes->process - 1)
// 		setup_inout_last(pipes);
// 	else
// 	{
// 		dup2(pipes->pipefd[i - 1][0], STDIN_FILENO);
// 		close(pipes->pipefd[i - 1][0]);
// 		dup2(pipes->pipefd[i][1], STDOUT_FILENO);
// 		close(pipes->pipefd[i][1]);
// 	}
// }
