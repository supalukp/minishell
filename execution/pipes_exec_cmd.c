/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:06:26 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/20 08:23:34 by spunyapr         ###   ########.fr       */
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

int	external_cmd_process(t_tree *tree, t_data *data)
{
	char	**args;
	char	**minishell_env;
	char	*paths;
	int		check;

	close_save_fd(tree);
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
		write(2, " ",1);
		write(2, ": command not found\n", 20);
		free_matrix(args);
		free(paths);
		free_matrix(minishell_env);
		close_save_fd(data->ast);
		return (127);
	}
	execve(paths, args, minishell_env);
	perror("execve failed");
	free_matrix(minishell_env);
	free_matrix(args);
	free(paths);
	return (126);
}

// int	external_cmd_process(t_tree *tree, t_data *data)
// {
// 	char	**args;
// 	char	*paths;
// 	char	**minishell_env;
// 	int		check;

// 	args = combine_cmdline(tree->cmd_line);
// 	if (!args)
// 		return (1);
// 	minishell_env = convert_env_lst_double_arrays(data->env);
// 	if (args[0][0] == '/' || args[0][0] == '.')
// 	{
// 		check = prepare_exec_path(args, &paths, minishell_env);
// 		if (check)
// 			return (127);
// 	}
// 	else
// 	{
// 		if (init_path(&paths, args, minishell_env))
// 			return (127);
// 	}
// 	execve(paths, args, minishell_env);
// 	perror("execve failed");
// 	close_save_fd(data->ast);
// 	free_matrix(minishell_env);
// 	free_matrix(args);
// 	free(paths);
// 	return (126);
// }
