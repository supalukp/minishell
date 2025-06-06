/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:46:44 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/06 15:30:31 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	handle_redirection_type(t_file *file, int *infile_fd)
{
	if (file->type == INFILE)
	{
		if (redirect_infile(file->content) == -1)
			*infile_fd = -1;
	}
	else if (file->type == OUTFILE && *infile_fd != -1)
	{
		if (redirect_outfile(file->content) == -1)
			return (-1);
	}
	else if (file->type == APPEND && *infile_fd != -1)
	{
		if (redirect_append(file->content) == -1)
			return (-1);
	}
	else if (file->type == HEREDOC)
	{
		if (redirect_heredoc(file->content) == -1 || *infile_fd == -1)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int	redirect_io(t_tree *token, t_pipes *pipes, t_data *data)
{
	t_file	*file;
	int		infile_fd;

	file = token->files;
	infile_fd = 0;
	while (file)
	{
		if (handle_redirection_type(file, &infile_fd) == -1)
			free_all_exit(data, pipes);
		file = file->next;
	}
	return (0);
}

int	redirect_one_cmd(t_tree *token)
{
	t_file	*file;
	int		infile_fd;

	file = token->files;
	infile_fd = 0;
	while (file)
	{
		if (handle_redirection_type(file, &infile_fd) == -1)
			return (-1);
		file = file->next;
	}
	return (0);
}

// int	redirect_io(t_tree *token, t_pipes *pipes, t_data *data)
// {
// 	t_file	*file;
// 	int		infile_fd;

// 	infile_fd = 0;
// 	file = token->files;
// 	while (file)
// 	{
// 		if (file->type == INFILE)
// 		{
// 			if (redirect_infile(file->content) == -1)
// 				infile_fd = -1;
// 		}
// 		else if (file->type == OUTFILE && infile_fd != -1)
// 		{
// 			if (redirect_outfile(file->content) == -1)
// 				free_all_exit(data, pipes);
// 		}
// 		else if (file->type == APPEND && infile_fd != -1)
// 		{
// 			if (redirect_append(file->content) == -1)
// 				free_all_exit(data, pipes);
// 		}
// 		else if (file->type == HEREDOC)
// 		{
// 			if (redirect_heredoc(file->content) == -1 || infile_fd == -1)
// 				free_all_exit(data, pipes);
// 		}
// 		else
// 			return (-1);
// 		file = file->next;
// 	}
// 	return (0);
// }

// int	redirect_one_cmd(t_tree *token)
// {
// 	t_file	*file;
// 	int		infile_fd;

// 	infile_fd = 0;
// 	file = token->files;
// 	while (file)
// 	{
// 		if (file->type == INFILE)
// 		{
// 			if (redirect_infile(file->content) == -1)
// 				infile_fd = -1;
// 		}
// 		else if (file->type == OUTFILE && infile_fd != -1)
// 		{
// 			if (redirect_outfile(file->content) == -1)
// 				return (-1);
// 		}
// 		else if (file->type == APPEND && infile_fd != -1)
// 		{
// 			if (redirect_append(file->content) == -1)
// 				return (-1);
// 		}
// 		else if (file->type == HEREDOC)
// 		{
// 			if (redirect_heredoc(file->content) == -1 || infile_fd == -1)
// 				return (-1);
// 		}
// 		else
// 			return (-1);
// 		file = file->next;
// 	}
// 	return (0);
// }
