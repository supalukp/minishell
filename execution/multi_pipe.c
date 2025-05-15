/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:06:42 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/15 17:00:06 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	close_unused_pipes(int i, t_pipes *pipes)
{
	int	j;

	j = 0;
	while (j < pipes->process)
	{
		if (j != i - 1)
			close(pipes->pipefd[j][0]);
		if (j != i)
			close(pipes->pipefd[j][1]);
		j++;
	}
}

void	setup_inout_first(t_pipes *pipes)
{
	dup2(pipes->pipefd[0][1], STDOUT_FILENO);
	close(pipes->pipefd[0][1]);
}

void	setup_inout_last(t_pipes *pipes)
{
	int	i;

	i = pipes->process - 1;
	dup2(pipes->pipefd[i - 1][0], STDIN_FILENO);
	close(pipes->pipefd[i - 1][0]);
	dup2(pipes->pipefd, STDOUT_FILENO);
	close(pipes->pipefd);
}

void	setup_inout(int i, t_pipes *pipes)
{
	if (i == 0)
		setup_inout_first(pipes);
	else if (i == pipes->process - 1)
		setup_inout_last(pipes);
	else
	{
		dup2(pipes->pipefd[i - 1][0], STDIN_FILENO);
		close(pipes->pipefd[i - 1][0]);
		dup2(pipes->pipefd[i][1], STDOUT_FILENO);
		close(pipes->pipefd[i][1]);
	}
}

int	process_child(int i, t_pipes *pipes, t_tree_token *tree, char **env, t_data *root)
{
	int	exit_status;

	close_unused_pipes(pipes, i);
	setup_inout(i, pipes);
	// execute_command(pipes->argv[i + 2], pipex);
}

t_pipe_cmds *create_pipe_cmd_node(t_tree_token *token)
{
	t_pipe_cmds *node;
	
	node = malloc(sizeof(t_pipe_cmds));
	if (!node)
		return (NULL);
	node->cmd = token;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_front(t_pipe_cmds **lst, t_pipe_cmds *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

t_pipe_cmds	*create_cmd_lst(t_tree_token *tree)
{
	t_pipe_cmds *lst;
	t_pipe_cmds *tmp;

	lst = NULL;
	if (tree->type != PIPE)
		return (NULL);
	while (tree->type == PIPE)
	{
		tmp = create_pipe_cmd_node(tree->right);
		if (!tmp)
			return (NULL);
		ft_lstadd_front(&lst, tmp);
		tree = tree->left;
	}
	tmp = create_pipe_cmd_node(tree->right);
	if (!tmp)
		return (NULL);
	ft_lstadd_front(&lst, tmp);
	tmp = create_pipe_cmd_node(tree->left);
	if (!tmp)
		return (NULL);
	ft_lstadd_front(&lst, tmp);
	return (lst);
}


int	pipe_multi_process(t_tree_token *tree, t_data *data, char **env,
		t_data *root)
{
	t_pipes		*pipes;
	t_pipe_cmds	*cmd_lst;
	int			i;

	pipes = init_pipes(tree);
	if (!pipes)
		return (perror("malloc failed"), EXIT_FAILURE);
	create_pipes(pipes);
	i = 0;
	while (i < pipes->process)
	{
		pipes->pid[i] = fork();
		if (pipes->pid[i] == -1)
			return (perror("Fork failed"), EXIT_FAILURE);
		if (pipes->pid[i] == 0)
			process_child(i, pipes, tree, env, root); // TODO
		i++;
	}
	process_parent(); // TODO
	return (0);
}
