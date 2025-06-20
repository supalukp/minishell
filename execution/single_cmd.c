/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:43:35 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/20 09:24:02 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	init_args_env(char ***args, char ***env, t_tree *tree, t_data *data)
{
	*args = combine_cmdline(tree->cmd_line);
	if (!*args)
		return (1);
	*env = convert_env_lst_double_arrays(data->env);
	return (0);
}

int	init_path(char **path, char **args, char **env)
{
	*path = get_path(args[0], env);
	if (!*path)
	{
		// free_matrix(env);
		return (command_not_found(args));
	}
	return (0);
}

int	resolve_path(char **args, char **env, char **path)
{
	int error;

	error = 0;
	
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		error = prepare_exec_path(args, path, env);
		if (error)
			return (error);
		return (0);
	}
	if (init_path(path, args, env))
	{
		return (127);
	}
	return (0);
}

int	fork_and_exec(char *path, char **args, char **env, t_data *data, t_stdio_backup *backup)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		free(path);
		return (free_matrix(env), free_matrix(args), 1);
	}
	if (pid == 0)
	{
		close(backup->stdin);
		close(backup->stdout);
		set_signal_to_default();
		child_execution(path, args, env, data);
	}
	else
		set_signal_to_ignore();
	free_matrix(env);
	return (wait_and_clean(0, pid, args, path));
}

int	external_single(t_tree *tree, t_data *data)
{
	t_stdio_backup	backup;
	char			**args;
	char			**env;
	char			*path;
	int				status;
	int path_ret;

	backup.stdin = dup(STDIN_FILENO);
	backup.stdout = dup(STDOUT_FILENO);
	path = NULL;
	if (save_fd_io(tree))
		return (close(backup.stdin), close(backup.stdout), 1);
	if (dup_for_one_cmd(tree))
		return (backup_std_io(backup.stdin, backup.stdout), 1);
	if (tree->cmd_line == NULL)
		return (backup_std_io(backup.stdin, backup.stdout), 0);
	if (init_args_env(&args, &env, tree, data))
		return (backup_std_io(backup.stdin, backup.stdout), 1);
	path_ret = resolve_path(args, env, &path);
	if (path_ret)
	{
		free_matrix(args);
		// free(path);
		free_matrix(env);
		return (backup_std_io(backup.stdin, backup.stdout), path_ret);
	}
	status = fork_and_exec(path, args, env, data, &backup);
	backup_std_io(backup.stdin, backup.stdout);
	return (status);
}

// int	external_single(t_tree *tree, t_data *data)
// {
// 	pid_t	pid;
// 	char	**args;
// 	char	**env;
// 	char	*path;
// 	int		stdin_backup;
// 	int		stdout_backup;
// 	int		status;
// 	int		check;
// 	int		redirect_status;

// 	stdin_backup = dup(STDIN_FILENO);
// 	stdout_backup = dup(STDOUT_FILENO);
// 	if (save_fd_io(tree))
// 		return (close(stdin_backup), close(stdout_backup), 1);
// 	redirect_status = dup_for_one_cmd(tree);
// 	if (redirect_status)
// 		return (backup_std_io(stdin_backup, stdout_backup), redirect_status);
// 	if (init_args_env(&args, &env, tree, data))
// 	{
// 		backup_std_io(stdin_backup, stdout_backup);
// 		return (1);
// 	}
// 	if (args[0][0] == '/' || args[0][0] == '.')
// 	{
// 		check = prepare_exec_path(args, &path, env);
// 		if (check)
// 		{
// 			backup_std_io(stdin_backup, stdout_backup);
// 			return (check);
// 		}
// 	}
// 	else
// 	{
// 		if (init_path(&path, args, env))
// 		{
// 			backup_std_io(stdin_backup, stdout_backup);
// 			return (127);
// 		}
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork failed");
// 		if (path)
// 			free(path);
// 		return (free_matrix(env), free_matrix(args), 1);
// 	}
// 	if (pid == 0)
// 	{
// 		set_signal_to_default();
// 		child_execution(path, args, env, data);
// 	}
// 	else
// 		set_signal_to_ignore();
// 	status = wait_and_clean(0, pid, args, path);
// 	backup_std_io(stdin_backup, stdout_backup);
// 	free_matrix(env);
// 	return (status);
// }
