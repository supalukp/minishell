/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:43:35 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/04 15:17:09 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	external_single(t_tree *tree, t_data *data)
{
	pid_t	pid;
	int		exit_status;
	char	**args;
	char	*paths;
	char 	**minishell_env;

	exit_status = 0;
	if (tree->files)
		if (redirect_one_cmd(tree) == -1)
			return (1);
	args = combine_cmdline(tree->cmd_line);
	if (!args)
		return (1);
	minishell_env = convert_env_lst_double_arrays(data->env);
	paths = get_path(args[0], minishell_env);
	if (!paths)
		return (free_matrix(minishell_env), command_not_found(args));
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (free_matrix(minishell_env), free_matrix(args), free(paths), 128 + errno);
	}
	if (pid == 0)
		child_execution(paths, args, minishell_env);
	free_matrix(minishell_env);
	return (wait_and_clean(exit_status, pid, args, paths));
}

void	child_execution(char *paths, char **args, char **minishell_env)
{
	execve(paths, args, minishell_env);
	perror("execve failed");
	free_matrix(minishell_env);
	free_matrix(args);
	free(paths);
	exit(126);
}

int	wait_and_clean(int exit_status, pid_t pid, char **args, char *paths)
{
	if (waitpid(pid, &exit_status, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
	free_matrix(args);
	free(paths);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	else if (WIFSIGNALED(exit_status))
		return (128 + WTERMSIG(exit_status));
	else
		return (EXIT_FAILURE);
}
