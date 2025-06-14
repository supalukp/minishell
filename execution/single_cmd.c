/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:43:35 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/12 16:55:04 by spunyapr         ###   ########.fr       */
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

char *get_program_name(char *path)
{
	char **split;
	char *res;
	int count;
	
	count = 0;
	split = ft_split(path, '/');
	if (!split)
		return (NULL);
	while (split[count])
		count++;
	res = ft_strdup(split[count - 1]);
	free(split);
	return (res);
}


int check_access_path(char *path)
{
	if (access(path, F_OK) == -1)
	{
		if (errno == ENOENT)
		{
			stderr_msg(path);
			stderr_msg(": No such file or directory\n");
		}
		else if (errno == EACCES)
		{
			stderr_msg(path);
			stderr_msg(": Permission denied\n");
		}
		else if (errno == ENOTDIR)
		{
			stderr_msg(path);
			stderr_msg(": Not a directory\n");
		}
		return (127);
	}
	return (0);
}

int prepare_exec_path(char **args, char **env, char **path)
{
	char *program_name;

	if (args[0][0] == '/')
	{
		if (check_access_path(args[0]))
			return (1);
		program_name = get_program_name(args[0]);
		args[0] = program_name;
		if (init_path(path, args, env))
			return (1);
	}
	else if (args[0][0] == '.')
	{
		*path = ft_strdup(args[0]);
		program_name = get_program_name(args[0]);
		args[0] = program_name;
	}
	else
	{
		if (init_path(path, args, env))
			return (1);
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
		return (close(stdin_backup), 1);
	if (prepare_exec_path(args, env, &path))
		return (free_matrix(env), free_matrix(args), close(stdin_backup), 127);
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (free_matrix(env), free_matrix(args), 1);
	}
	if (pid == 0)
		child_execution(path, args, env);
	free_matrix(env);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	return (wait_and_clean(0, pid, args, path));
}
