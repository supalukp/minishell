/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:46:44 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/26 17:46:04 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int redirect_infile(char *filename)
{
    int fd;
	
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening infile");
	    return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 failed for input redirection");
		close(fd);
		return (-1);
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
		return (-1);
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
		return (-1);
	}
	close(fd);
	return (0);
}


// int redirect_io(t_tree_token *token, t_pipes *pipes, t_data *data)
// {
//     t_file *file;
// 	i

//     file = token->files;
    
//     while (file)
//     {
//         if (file->type == INFILE)
// 		{
// 			redirect_infile(file->content);
// 		}
//         else if (file->type == OUTFILE )
// 			redirect_outfile(file->content);
// 		else if (file->type == APPEND)
// 			redirect_append(file->content);
//         else if (file->type == HEREDOC)
// 			redirect_heredoc(file->content);
//         else 
//             return (-1);
//         file = file->next;
//     }
//     return (0);
// }



int redirect_io(t_tree_token *token, t_pipes *pipes, t_data *data)
{
    t_file *file;
	int infile_fd;
	
	infile_fd = 0;
	file = token->files;
    while (file)
    {
        if (file->type == INFILE)
		{
			if (redirect_infile(file->content) == -1)
				infile_fd = -1;
		}
        else if (file->type == OUTFILE && infile_fd != -1)
		{
			if (redirect_outfile(file->content) == -1)
				free_all_exit(data, pipes);
		}
		else if (file->type == APPEND && infile_fd != -1)
		{
			if (redirect_append(file->content) == -1)
				free_all_exit(data, pipes);
		}
        else if (file->type == HEREDOC)
		{
			if (redirect_heredoc(file->content) == -1 || infile_fd == -1)
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
	int infile_fd;

	infile_fd = 0;
	file = token->files;
    while (file)
    {
        if (file->type == INFILE)
		{
			if (redirect_infile(file->content) == -1)
				infile_fd = -1;
		}
        else if (file->type == OUTFILE && infile_fd != -1)
		{
			if (redirect_outfile(file->content) == -1)
				return (-1);
		}
		else if (file->type == APPEND && infile_fd != -1)
		{
			if (redirect_append(file->content) == -1)
				return (-1);
		}
        else if (file->type == HEREDOC)
		{
			if (redirect_heredoc(file->content) == -1 || infile_fd == -1)
				return (-1);
		}
        else 
            return (-1);
        file = file->next;
    }
    return (0);
}
