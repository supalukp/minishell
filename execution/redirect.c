/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:46:44 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/17 21:13:45 by spunyapr         ###   ########.fr       */
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
	    exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
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

int redirect_io(t_tree_token *token)
{
    t_file *file;

    file = token->files;
    
    while (file)
    {
        if (token->files->type == INFILE)
            redirect_infile(file->content);
        else if (token->files->type == OUTFILE)
            redirect_outfile(file->content);
        else if (token->files->type == APPEND)
            redirect_append(file->content);
        // else if (token->files->type == HEREDOC)
        //     redirect_heredoc(file->content);
        else 
            return (-1);
        file = file->next;
    }
    return (0);
}