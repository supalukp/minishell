/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:46:20 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/22 11:51:36 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	count_pipes(t_tree_token *tree)
{
	t_tree_token	*token;
	int				count;

	token = tree;
	count = 0;
	while (token->type == PIPE)
	{
		count++;
		token = token->left;
	}
	return (count);
}

int	**create_double_fd(int pipe_count)
{
	int	i;
	int	**fd;

	fd = (int **)malloc(sizeof(int *) * (pipe_count + 1));
	if (!fd)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			free_double_array(fd);
			return (NULL);
		}
		i++;
	}
	fd[pipe_count] = NULL;
	return (fd);
}

t_pipes *init_pipes(t_tree_token *tree)
{
	int i;
    t_pipes *pipes;

    pipes =  malloc(sizeof(t_pipes));
    if (!pipes)
        return (NULL);
    pipes->pipes_count = count_pipes(tree);
    pipes->process = pipes->pipes_count + 1;
    pipes->pipefd = create_double_fd(pipes->pipes_count);
    if (!pipes->pipefd)
        return (perror("malloc fd failed"), NULL);
    pipes->pid = malloc(sizeof(pid_t) * (pipes->process));
    if (!pipes->pid)
    {
        free_double_array(pipes->pipefd);
    	free(pipes);
        return (perror("malloc pid failed"), NULL);
    }
	i = -1;
	while (++i < pipes->process)
		pipes->pid[i] = -1;
	pipes->cmd_lst = create_cmd_lst(tree);
	if (!pipes->cmd_lst)
	{
		free_pipes_struct(pipes);
		return (perror("create cmd list failed"), NULL);
	}
	return (pipes);
}

void free_pipes(t_pipes *pipes)
{
	if (!pipes)
		return ;
	if (pipes->pipefd)
		free_double_array(pipes->pipefd);
	if (pipes->pid)
		free(pipes->pid);
	if (pipes)
		free(pipes);
}

void create_pipes(t_pipes *pipes)
{
    int i;
    
    i = 0;
    while (i < pipes->pipes_count)
    {
        if (pipe(pipes->pipefd[i]) == -1)
            perror("Failed to create pipes");
        i++;
    }
}

