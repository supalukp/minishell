/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ll_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:28:09 by syukna            #+#    #+#             */
/*   Updated: 2025/06/04 15:13:24 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	add_cmd_file(char *ctt, t_type type, t_tree *ln, int *error)
{
	t_file *file;
	t_file *temp_file;
	
	file = ft_calloc(1, sizeof(t_file));
	if (!file)
	{
		*error = 1;
		free (ctt);
		return ;
	}
	file->content = ctt;
	file->type = type;
	file->next = NULL;
	if (!ln->files)
		ln->files = file;
	else
	{
		temp_file = ln->files;
		while (temp_file->next)
			temp_file = temp_file->next;
		temp_file->next = file;
	}	
}