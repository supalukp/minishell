/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:10:05 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/27 10:28:38 by spunyapr         ###   ########.fr       */
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
			exit_status = exec_buildin(tree, data);
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
		if (redirect_one_cmd(tree) == -1)
			return (1);
	args = combine_cmdline(tree->cmd_line);
	if (!args)
		return (1);
	paths = get_path(args[0], env);
	if (!paths)
	{
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": command not found\n", 20);
		free_matrix(args);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free_matrix(args);
		free(paths);
		return (128 + errno);
	}
	if (pid == 0)
	{
		execve(paths, args, env);
		perror("execve failed");
		free_matrix(args);
		free(paths);
		exit(126);
	}
	else
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
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": command not found\n", 20);
		free_matrix(args);
		return (127);
	}
	execve(paths, args, env);
	perror("execve failed");
	free_matrix(args);
	free(paths);
	return(126);
}
