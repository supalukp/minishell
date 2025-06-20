/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:06:42 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/20 08:38:22 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	pipe_multi_process(t_tree *tree, t_data *data)
{
	t_pipes	*pipes;
	int		status;

	pipes = init_pipes(tree, data);
	if (!pipes)
		return (perror("malloc failed"), EXIT_FAILURE);
	create_pipes(pipes);
	// print_all(data);
	if (fork_and_exec_children(pipes, data) != 0)
	{
		// close_save_fd(data->ast);
		return (EXIT_FAILURE);
	}
	status = process_parent(pipes);
	
	// close_save_fd(data->ast);
	return (status);
}
