/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:06:26 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 13:38:27 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	prepare_exec(char **args, char **path, char **env)
{
	if (args[0][0] == '/' || args[0][0] == '.')
		return (prepare_exec_path(args, path, env));
	return (init_path(path, args, env));
}

static char	**prepare_env_and_args(t_tree *tree, t_data *data, char ***args)
{
	*args = combine_cmdline(tree->cmd_line);
	if (!*args)
		return (NULL);
	return (convert_env_lst_double_arrays(data->env));
}

static void	free_pipe_cmd(char **env, char **args, char *paths)
{
	if (env)
		free_matrix(env);
	if (args)
		free_matrix(args);
	if (paths)
		free(paths);
}

int	external_cmd_process(t_tree *tree, t_data *data)
{
	char	**args;
	char	**minishell_env;
	char	*paths;
	int		check;

	close_save_fd(tree);
	if (ft_strcmp(tree->cmd_line->content, "") == 0)
		return (0);
	minishell_env = prepare_env_and_args(tree, data, &args);
	if (!minishell_env)
		return (1);
	check = prepare_exec(args, &paths, minishell_env);
	if (check)
	{
		free_matrix(args);
		free_matrix(minishell_env);
		return (check);
	}
	if (args[0][0] == '\0')
	{
		free_pipe_cmd(minishell_env, args, paths);
		return (command_not_found(args));
	}
	execve(paths, args, minishell_env);
	perror("execve failed");
	free_pipe_cmd(minishell_env, args, paths);
	return (126);
}
