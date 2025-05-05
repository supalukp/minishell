/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:10:05 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/05 16:29:18 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	main_execution(t_token *tree, char **env)
{
	int	exit_status;

	exit_status = 0;
	// Build a tree start from root
	if (!tree)
		return (0);
	if (tree->type == PIPE)
		exit_status = pipe_process(tree, env); // TODO
	else if (tree->type == CMD)
	{
		if (is_buildin(tree->name) == true)
			exit_status = exec_buildin(tree->name);
		else
			exit_status = simple_command_process(tree, env); // TODO
	}
	// else
	//     return (handle_unexpected_type(tree)); // TODO
	return (exit_status);
}

int	simple_command_process(t_token *tree, char **env)
{
	pid_t	pid;
	int		exit_status;
	char	**args;
	char	*paths;

	args = ft_split(tree->name, ' ');
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

int	pipe_process(t_token *tree, char **env)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		exit_status;

	exit_status = 0;
	if (pipe(pipefd) == -1)
		return (perror("pipe failed"), EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork failed"), EXIT_FAILURE);
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(main_execution(tree->left, env));
	}
	pid2 = fork();
	if (pid2 == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(main_execution(tree->right, env));
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &exit_status, 0);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_FAILURE);
}

// else if (WIFSIGNALED(exit_status))
//     return (128 + WTERMSIG(exit_status));
