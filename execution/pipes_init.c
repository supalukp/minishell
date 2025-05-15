/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:46:20 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/15 16:05:40 by spunyapr         ###   ########.fr       */
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

int	**create_double_fd(int process_num)
{
	int	i;
	int	**fd;

	fd = (int **)malloc(sizeof(int *) * (process_num + 1));
	if (!fd)
		return (NULL);
	i = 0;
	while (i < process_num)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			free_double_array(fd);
			return (NULL);
		}
		i++;
	}
	fd[process_num] = NULL;
	return (fd);
}

t_pipes *init_pipes(t_tree_token *tree)
{
    t_pipes *pipes;

    pipes =  malloc(sizeof(t_pipes));
    if (!pipes)
        return (NULL);
    pipes->pipes_count = count_pipes(tree);
    pipes->process = pipes->pipes_count + 1;
    pipes->pipefd = create_double_fd(pipes->process);
    if (!pipes->pipefd)
        return (perror("malloc fd failed"), NULL);
    pipes->pid = malloc(sizeof(pid_t) * (pipes->process));
    if (!pipes->pid)
    {
        free_double_array(pipes->pipefd);
        return (perror("malloc pid failed"), NULL);
    }
}

void create_pipes(t_pipes *pipes)
{
    int i;
    
    i = 0;
    while (i < pipes->process)
    {
        if (pipe(pipes->pipefd[i]) == -1)
            perror("Failed to create pipes");
        i++;
    }
}
