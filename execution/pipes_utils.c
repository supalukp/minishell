/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:33:38 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/04 08:17:05 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	free_double_array(int **double_array)
{
	int	i;

	i = 0;
	if (!double_array)
		return ;
	while (double_array[i])
	{
		free(double_array[i]);
		double_array[i] = NULL;
		i++;
	}
	free(double_array);
	double_array = NULL;
}

void	free_cmd_lst(t_pipe_cmds *cmd_lst)
{
	t_pipe_cmds	*tmp;

	while (cmd_lst)
	{
		tmp = cmd_lst->next;
		free(cmd_lst);
		cmd_lst = tmp;
	}
}

void	free_pipes_struct(t_pipes *pipes)
{
	if (!pipes)
		return ;
	if (pipes->pipefd)
		free_double_array(pipes->pipefd);
	if (pipes->pid)
		free(pipes->pid);
	if (pipes->cmd_lst)
		free_cmd_lst(pipes->cmd_lst);
	free(pipes);
}

void	free_all_exit(t_data *data, t_pipes *pipes)
{
	if (data)
		free_program(data);
	if (pipes)
		free_pipes_struct(pipes);
	exit(1);
}
