/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:10:05 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/24 14:34:05 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	main_execution(t_tree_token *tree, char **env, t_data *data)
{
	int	exit_status;

	exit_status = 0;

	if (!tree)
		return (0);
	if (tree->type == PIPE)
		exit_status = pipe_multi_process(tree, env, data);
	else if (tree->type == CMD_LINE)
	{
		if (is_buildin(tree) == true)
		{
			if (tree->files)
				if (redirect_one_cmd(tree) == -1)
					return (1);
			exit_status = exec_buildin(tree);
		}
		else if (tree->left == NULL && tree->right == NULL)
			exit_status = external_single(tree, env);
		else
			exit_status = external_cmd_process(tree, env);
	}
	// else
	//     return (handle_unexpected_type(tree)); // TODO
	return (exit_status);
}

char **combine_cmdline(t_cmd_element *args)
{
	char **res;
	int count;
	int i;
	t_cmd_element *tmp;
	
	count = 0;
	tmp = args;
	while(tmp)
	{
		count++;
		tmp = tmp->next;	
	}
	res = malloc(sizeof(char *) * (count + 1));
	i = 0;
	tmp = args;
	while (tmp)
	{
		res[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	external_single(t_tree_token *tree, char **env)
{
	pid_t	pid;
	int		exit_status;
	char	**args;
	char	*paths;

	if (tree->files)
		redirect_one_cmd(tree);
	args = combine_cmdline(tree->cmd_line);
	if (!args)
		return (1);
	paths = get_path(args[0], env);
	if (!paths)
	{
		free_matrix(args);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free_matrix(args);
		free(paths);
		return (1);
	}
	if (pid == 0)
	{
		execve(paths, args, env);
		perror("execve failed");
		free_matrix(args);
		free(paths);
		exit(1);
	}
	else
	{
		waitpid(pid, &exit_status, 0);
		free_matrix(args);
		free(paths);
		if (WIFEXITED(exit_status))
			return (WEXITSTATUS(exit_status));
		else
			return (EXIT_FAILURE);
	}
}

int	external_cmd_process(t_tree_token *tree, char **env)
{
	char	**args;
	char	*paths;

	args = combine_cmdline(tree->cmd_line);
	if (!args)
		return (1);
	paths = get_path(args[0], env);
	if (!paths)
	{
		free_matrix(args);
		return (127);
	}
	execve(paths, args, env);
	perror("execve failed");
	free_matrix(args);
	free(paths);
	exit(1);
}
int	pipe_process(t_tree_token *tree, char **env, t_data *data)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		exit_status1;
	int		exit_status2;

	if (pipe(pipefd) == -1)
		return (perror("pipe failed"), EXIT_FAILURE);
	if (tree->left->type != PIPE)
	{
		pid1 = fork();
		if (pid1 == -1)
			return (perror("fork failed"), EXIT_FAILURE);
		if (pid1 == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			exit_status1 = main_execution(tree->left, env, data);
			free_program(data);
			exit(exit_status1);
		}
	}
	else
		exit_status1 = main_execution(tree->left, env, data);
	pid2 = fork();
	if (pid2 == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit_status2 = main_execution(tree->right, env, data);
		free_program(data);
		exit(exit_status2);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	if (tree->left->type != PIPE)
		waitpid(pid1, NULL, 0);
	waitpid(pid2, &exit_status2, 0);
	if (WIFEXITED(exit_status2))
		return (WEXITSTATUS(exit_status2));
	return (EXIT_FAILURE);
}
