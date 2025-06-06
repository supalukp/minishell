/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:43:35 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/06 15:08:54 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	handle_redirect(t_tree *tree)
{
	if (tree->files)
		if (redirect_one_cmd(tree) == -1)
			return (1);
	return (0);
}

static int	init_args_env(char ***args, char ***env, t_tree *tree, t_data *data)
{
	*args = combine_cmdline(tree->cmd_line);
	if (!*args)
		return (1);
	*env = convert_env_lst_double_arrays(data->env);
	return (0);
}

static int	init_path(char **path, char **args, char **env)
{
	*path = get_path(args[0], env);
	if (!*path)
	{
		free_matrix(env);
		return (command_not_found(args));
	}
	return (0);
}

int	external_single(t_tree *tree, t_data *data)
{
	pid_t	pid;
	char	**args;
	char	**env;
	char	*path;
	int		stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	if (handle_redirect(tree))
		return (1);
	if (init_args_env(&args, &env, tree, data))
		return (1);
	if (init_path(&path, args, env))
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free_matrix(env);
		free_matrix(args);
		return (1);
	}
	if (pid == 0)
		child_execution(path, args, env);
	free_matrix(env);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	return (wait_and_clean(0, pid, args, path));
}
