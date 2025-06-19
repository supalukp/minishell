/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:10:05 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 23:01:14 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	main_execution(t_tree *tree, t_data *data)
{
	int	exit_status;
	// int	error;

	exit_status = 0;
	// error = 0;
	if (!tree)
		return (0);
	if (tree->type == PIPE)
		exit_status = pipe_multi_process(tree, data);
	else if (tree->type == AND)
	{
		exit_status = main_execution(tree->left, data);
		if (exit_status == 0)
			exit_status = main_execution(tree->right, data);
	}
	else if (tree->type == OR)
	{
		exit_status = main_execution(tree->left, data);
		if (exit_status != 0)
			exit_status = main_execution(tree->right, data);
	}
	else if (tree->type == CMD_LINE)
	{
		// command_line_maker(tree, &error, data);
		// print_all(data);
		// if (error)
		// 	return (1);
		exit_status = exec_cmd_line(tree, data, exit_status);
	}
	else
		exit_status = 1;
	return (exit_status);
}
