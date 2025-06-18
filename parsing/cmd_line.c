/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:35:34 by syukna            #+#    #+#             */
/*   Updated: 2025/06/17 19:20:39 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	command_line_maker(t_tree *cmd_line, int *error, t_data *request)
{
	identify_redirections(cmd_line, error);
	remove_quotes_redirections(cmd_line);
	split_cmd_elements(cmd_line, error);
	if (*error)
		return ;
	add_expansions(cmd_line, request->env, request);
	merge_cmd_quotes(cmd_line);
}
