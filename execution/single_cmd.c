/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:43:35 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/14 18:23:28 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	handle_redirect(t_tree *tree)
{
	int ret;
	
	if (tree->files)
	{
		ret = redirect_one_cmd(tree);
		if (ret)
			return (ret);
	}
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

int	init_path(char **path, char **args, char **env)
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
	int i;
	
	count = 0;
	split = ft_split(path, '/');
	if (!split)
		return (NULL);
	while (split[count])
		count++;
	res = ft_strdup(split[count - 1]);
	i = -1;
	while(split[++i])
		free(split[i]);	
	free(split);
	return (res);
}


int check_access_path(char *path)
{
	struct stat	st;

	if (access(path, F_OK) == -1)
	{
		if (errno == ENOENT)
		{
			stderr_msg(path);
			stderr_msg(": No such file or directory\n");
			return (127);
		}
		else if (errno == EACCES)
		{
			stderr_msg(path);
			stderr_msg(": Permission denied\n");
			return (126);
		}
		else if (errno == ENOTDIR)
		{
			stderr_msg(path);
			stderr_msg(": Not a directory\n");
			return (126);
		}
	}
	if (stat(path, &st) == 0)
    {
		if (S_ISDIR(st.st_mode))
        {
            stderr_msg(path);
			stderr_msg(": Is a directory\n");
            return (126);
        }
	}
	return (0);
}

int prepare_exec_path(char **args, char **path, char **env)
{
	char *program_name;
	int check;
	
	if (args[0][0] == '/')
	{
		check = check_access_path(args[0]);
		if (check)
			return (check);
		program_name = get_program_name(args[0]);
		free(args[0]);  
		args[0] = program_name;
		if (init_path(path, args, env))
			return (1);
	}
	else if (args[0][0] == '.')
	{
		*path = ft_strdup(args[0]);
		program_name = get_program_name(args[0]);
		free(args[0]);  
		args[0] = program_name;
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
	int status;
	int check;
	int redirect_status;
	
	stdin_backup = dup(STDIN_FILENO);
	redirect_status =  handle_redirect(tree);
	// if (redirect_status)
	// 	return (close(stdin_backup), redirect_status)
	// signal(SIGINT, SIG_IGN);
	if (init_args_env(&args, &env, tree, data))
		return (close(stdin_backup), 1);
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		check = prepare_exec_path(args, &path, env);
		if (check)
		{
			if (env)
				free_matrix(env);
			if (args)
				free_matrix(args);
			close(stdin_backup);
			return (check);
		}
	}
	else 
	{
		if (init_path(&path, args, env))
			return (close(stdin_backup), 127);
	}
	if (g_signal == SIGINT)
	{
		free_matrix(env);
		if (args)
			free_matrix(args);
		if (path)
			free(path);
		return(130);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		if (path)
            free(path);
		return (free_matrix(env), free_matrix(args), 1);
	}
	if (pid == 0)
		child_execution(path, args, env);
	free_matrix(env);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	status = wait_and_clean(0, pid, args, path);
	return (status);
}
