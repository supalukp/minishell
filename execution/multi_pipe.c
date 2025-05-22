/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:06:42 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/22 14:44:46 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	close_unused_pipes(int i, t_pipes *pipes)
{
	int	j;

	j = 0;
	while (j < pipes->pipes_count)
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

int	process_child(int i, t_pipes *pipes, t_pipe_cmds *cmd_lst, char **env, t_data *data)
{
	int	exit_status;

	exit_status = 0;
	close_unused_pipes(i, pipes);
	setup_inout(i, pipes);
	redirect_io(cmd_lst->cmd, pipes, data);
	if (is_buildin(cmd_lst->cmd) == true)
	{
		exit_status = exec_buildin(cmd_lst->cmd);
		if (data)
			free_program(data);
		// if (pipes)
		// 	free_pipes_struct(pipes);
	}
	else if (cmd_lst->cmd->type == CMD_LINE)
		exit_status = external_cmd_process(cmd_lst->cmd, env);
	return (exit_status);
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

void	ft_lstadd_cmd_front(t_pipe_cmds **lst, t_pipe_cmds *new)
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
		ft_lstadd_cmd_front(&lst, tmp);
		if (tree->left->type != PIPE)
			break;
		tree = tree->left;
	}
	tmp = create_pipe_cmd_node(tree->left);
	if (!tmp)
		return (NULL);
	ft_lstadd_cmd_front(&lst, tmp);
	return (lst);
}

int	process_parent(t_pipes *pipes)
{
	int	i;
	int status;
	int last_exit_status;

	i = -1;
	last_exit_status = 0;
	while (++i < pipes->pipes_count)
	{
		close(pipes->pipefd[i][0]);
		close(pipes->pipefd[i][1]);
	}
	i = -1;
	while (++i < pipes->process)
	{
		if (waitpid(pipes->pid[i], &status, 0) == -1)
            perror("waitpid failed");
		else if (WIFEXITED(status))
            last_exit_status = WEXITSTATUS(status);
	}
	if (pipes)
		free_pipes_struct(pipes);
	return (last_exit_status);
}

int	pipe_multi_process(t_tree_token *tree, char **env, t_data *data)
{
	t_pipes		*pipes;
	t_pipe_cmds *tmp;
	int			i;
	int exit_status;
	int last_exit_status;

	pipes = init_pipes(tree);
	if (!pipes)
		return (perror("malloc failed"), EXIT_FAILURE);
	create_pipes(pipes);
	i = -1;
	tmp = pipes->cmd_lst;
	while (++i < pipes->process && tmp)
	{
		pipes->pid[i] = fork();
		if (pipes->pid[i] == -1)
			return (perror("Fork failed"), EXIT_FAILURE);
		if (pipes->pid[i] == 0)
		{
			exit_status = process_child(i, pipes, tmp, env, data);
			free_pipes_struct(pipes);
			exit(exit_status);
		}
		tmp = tmp->next;
	}
	last_exit_status = process_parent(pipes);
	return (last_exit_status);
}
