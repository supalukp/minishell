/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:35:34 by syukna            #+#    #+#             */
/*   Updated: 2025/05/28 15:47:52 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	command_line_maker(t_tree *cmd_line, int *error)
{
	identify_redirections(cmd_line, error);
	if (*error)
		return ;
	split_cmd_elements(cmd_line, error);
}
