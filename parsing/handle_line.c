/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:43:49 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/18 09:18:39 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	process_ast(char *line, t_data *request)
{
	t_tree	*tree;
	int		exit_status;

	tree = mns_parse(line);
	request->ast = tree;
	if (!request->ast)
		return (0);
	exit_status = traverse_heredoc(request->ast, request);
	if (exit_status != 0)
		return (exit_status);
	request->last_exit = main_execution(request->ast, request);
	close_save_fd(request->ast);
	return (0);
}

void	handle_line(char *line, t_data *request)
{
	int	exit_status;

	exit_status = error_checking(line, request);
	if (exit_status != 0)
		return (request->last_exit = exit_status, (void)0);
	if (only_space(line) || only_colon(line) || only_exclamation(line))
		return ;
	exit_status = process_ast(line, request);
	if (exit_status != 0)
		request->last_exit = exit_status;
	clean_data(request);
}

// void	handle_line(char *line, t_data *request)
// {
// 	t_tree	*tree;
// 	int		exit_status;

// 	exit_status = error_checking(line, request);
// 	if (exit_status != 0)
// 	{
// 		request->last_exit = exit_status;
// 		return ;
// 	}
// 	if (only_space(line) || only_colon(line) || only_exclamation(line))
// 		return ;
// 	tree = mns_parse(line);
// 	request->ast = tree;
// 	if (request->ast)
// 	{
// 		exit_status = traverse_heredoc(request->ast, request);
// 		if (exit_status != 0)
// 		{
// 			request->last_exit = exit_status;
// 			clean_data(request);
// 			return ;
// 		}
// 		request->last_exit = main_execution(request->ast, request);
// 		close_save_fd(request->ast);
// 		clean_data(request);
// 	}
// }
