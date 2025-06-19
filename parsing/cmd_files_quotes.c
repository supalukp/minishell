/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_files_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:35:41 by syukna            #+#    #+#             */
/*   Updated: 2025/06/18 19:36:59 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	remove_quotes_red(t_file *file)
{
	int	len;

	len = ft_strlen(file->content);
	if (!includedchar(file->content[0], "'\""))
		return ;
	if (file->content[0] == '\'')
	{
		file->content[len - 1] = '\0';
		memmove(file->content, &file->content[1], len - 1);
		file->quoted = 1;
	}
	if (file->content[0] == '\"')
	{
		file->content[len - 1] = '\0';
		memmove(file->content, &file->content[1], len - 1);
		file->quoted = 2;
	}
}

void	remove_quotes_redirections(t_tree *cmd_line)
{
	t_file	*file;

	file = cmd_line->files;
	if (file == NULL)
		return ;
	while (file)
	{
		remove_quotes_red(file);
		file = file->next;
	}
}
