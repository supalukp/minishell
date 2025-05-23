/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:35:34 by syukna            #+#    #+#             */
/*   Updated: 2025/05/23 13:43:40 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	command_line_maker(t_tree_token *cmd_line)
{
	identify_redirections(cmd_line);
	split_cmd_elements(cmd_line);
}

// 1. quotes first ?
// 2. Handle second level operators < > << >>. No need to separate such operators from their FILE
// 3. handle environments