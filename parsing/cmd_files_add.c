/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_files_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:28:09 by syukna            #+#    #+#             */
/*   Updated: 2025/06/18 19:39:13 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	add_cmd_file(char *ctt, t_type type, t_tree *ln, int *error)
{
	t_file	*file;
	t_file	*temp_file;

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

void	get_redirections(int index, t_tree *cmd_line, int *error)
{
	int		i;
	char	*filename;
	t_type	filetype;

	if (!cmd_line || !cmd_line->content || *error)
		return ;
	i = index;
	filetype = define_redirection_type(i, cmd_line->content);
	while (is_letters(cmd_line->content[i], "< >"))
		i++;
	filename = get_redirection_file(i, cmd_line->content, error);
	if (!filename)
	{
		*error = 1;
		return ;
	}
	remove_redirection(index, cmd_line, error);
	if (*error)
	{
		free(filename);
		return ;
	}
	add_cmd_file(filename, filetype, cmd_line, error);
}

char	*get_redirection_file(int index, char *cmd_line, int *error)
{
	int		i;
	int		j;
	char	*file_name;

	i = 0;
	j = 0;
	while (cmd_line[i + index] == ' ')
		index++;
	while (cmd_line[i + index] != ' ' && cmd_line[i + index] != '\0')
		i++;
	file_name = ft_calloc(i + 1, sizeof(char));
	if (!file_name)
	{
		free(cmd_line);
		return (*error = 1, NULL); // TODO exit
	}
	while (j < i)
	{
		file_name[j] = cmd_line[index + j];
		j++;
	}
	return (file_name);
}
