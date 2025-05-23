/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ll_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:28:09 by syukna            #+#    #+#             */
/*   Updated: 2025/05/22 14:34:10 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	add_cmd_file(char *content, t_type type, t_tree_token *cmdline)
{
	t_file *file;
	t_file *temp_file;
	
	file = malloc(sizeof(t_file));
	if (!file)
		return ; //TODO exit function
	file->content = content;
	file->type = type;
	file->next = NULL;
	if (!cmdline->redirections)
		cmdline->redirections = file;
	else
	{
		temp_file = cmdline->redirections;
		while (temp_file->next)
			temp_file = temp_file->next;
		temp_file->next = file;
	}	
}