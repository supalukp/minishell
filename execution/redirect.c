/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:46:44 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/22 15:34:38 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int redirect_infile(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
	    return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 failed for input redirection");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (0);
}

int	redirect_outfile(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening output file");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed for output redirection");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (0);
}

int	redirect_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error opening file for append");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed for append redirection");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (0);
}

int redirect_io(t_tree_token *token, t_pipes *pipes, t_data *data)
{
    t_file *file;

    file = token->files;
    
    while (file)
    {
        if (token->files->type == INFILE)
		{
			if (redirect_infile(file->content) == -1)
				free_all_exit(data, pipes);
		}
        else if (token->files->type == OUTFILE)
		{
			if (redirect_outfile(file->content) == -1)
				free_all_exit(data, pipes);
		}
		else if (token->files->type == APPEND)
		{
			if (redirect_append(file->content) == -1)
				free_all_exit(data, pipes);
		}
        else if (token->files->type == HEREDOC)
		{
			if (redirect_heredoc(file->content) == -1)
				free_all_exit(data, pipes);
		}
        else 
            return (-1);
        file = file->next;
    }
    return (0);
}

int redirect_one_cmd(t_tree_token *token)
{
    t_file *file;

    file = token->files;
    
    while (file)
    {
        if (token->files->type == INFILE)
		{
			if (redirect_infile(file->content) == -1)
				return (-1);
		}
        else if (token->files->type == OUTFILE)
		{
			if (redirect_outfile(file->content) == -1)
				return (-1);
		}
		else if (token->files->type == APPEND)
		{
			if (redirect_append(file->content) == -1)
				return (-1);
		}
        else if (token->files->type == HEREDOC)
		{
			if (redirect_heredoc(file->content) == -1)
				return (-1);
		}
        else 
            return (-1);
        file = file->next;
    }
    return (0);
}