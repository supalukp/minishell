/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:10:05 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 09:12:56 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	main_execution(t_tree *tree, t_data *data)
{
	int	exit_status;

	exit_status = 0;
	if (!tree)
		return (0);
	if (tree->type == PIPE)
		exit_status = pipe_multi_process(tree, data);
	else if (tree->type == AND)
	{
		exit_status = main_execution(tree->left, data);
		if (exit_status == 0)
			exit_status = main_execution(tree->right, data);
	}
	else if (tree->type == OR)
	{
		exit_status = main_execution(tree->left, data);
		if (exit_status != 0)
			exit_status = main_execution(tree->right, data);
	}
	else if (tree->type == CMD_LINE)
		exit_status = exec_cmd_line(tree, data, exit_status);
	else
		exit_status = 1;
	return (exit_status);
}

static int	execute_builtin_with_redirects(t_tree *tree, t_data *data)
{
	int	stdin_backup;
	int	stdout_backup;
	int	redirect_status;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (save_fd_io(tree))
		return (close(stdin_backup), close(stdout_backup), 1);
	redirect_status = dup_for_one_cmd(tree);
	if (redirect_status)
		return (backup_std_io(stdin_backup, stdout_backup), redirect_status);
	if (ft_strcmp(tree->cmd_line->content, "exit") == 0)
		backup_std_io(stdin_backup, stdout_backup);
	redirect_status = exec_buildin(tree, data);
	backup_std_io(stdin_backup, stdout_backup);
	return (redirect_status);
}

int	exec_cmd_line(t_tree *tree, t_data *data, int exit_status)
{
	if (!tree->cmd_line)
		return (0);
	if (is_buildin(tree))
		return (execute_builtin_with_redirects(tree, data));
	if (!tree->left && !tree->right)
		exit_status = external_single(tree, data);
	else
		exit_status = external_cmd_process(tree, data);
	return (exit_status);
}

// int	exec_cmd_line(t_tree *tree, t_data *data, int exit_status)
// {
// 	int	stdin_backup;
// 	int	stdout_backup;
// 	int	redirect_status;

// 	if (tree->cmd_line == NULL)
// 		return (0);
// 	if (is_buildin(tree) == true)
// 	{
// 		stdin_backup = dup(STDIN_FILENO);
// 		stdout_backup = dup(STDOUT_FILENO);
// 		if (save_fd_io(tree))
// 			return (close(stdin_backup), close(stdout_backup), 1);
// 		redirect_status = dup_for_one_cmd(tree);
// 		if (redirect_status)
// 			return (backup_std_io(stdin_backup, stdout_backup),
// 				redirect_status);
// 		if (ft_strcmp(tree->cmd_line->content, "exit") == 0)
// 			backup_std_io(stdin_backup, stdout_backup);
// 		exit_status = exec_buildin(tree, data);
// 		backup_std_io(stdin_backup, stdout_backup);
// 	}
// 	else if (tree->left == NULL && tree->right == NULL)
// 		exit_status = external_single(tree, data);
// 	else
// 		exit_status = external_cmd_process(tree, data);
// 	return (exit_status);
// }

int	count_cmd_element(t_cmd_element *args)
{
	t_cmd_element	*tmp;
	int				count;

	count = 0;
	tmp = args;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	**alloc_cmd_array(int count)
{
	char	**res;

	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	return (res);
}

static int	fill_cmd_array(char **res, t_cmd_element *args)
{
	int				i;
	t_cmd_element	*tmp;

	i = 0;
	tmp = args;
	while (tmp)
	{
		res[i] = ft_strdup(tmp->content);
		if (!res[i])
		{
			while (i--)
				free(res[i]);
			free(res);
			return (1);
		}
		tmp = tmp->next;
		i++;
	}
	res[i] = NULL;
	return (0);
}

char	**combine_cmdline(t_cmd_element *args)
{
	char	**res;
	int		count;

	count = count_cmd_element(args);
	if (count == 0)
		return (NULL);
	res = alloc_cmd_array(count);
	if (!res)
		return (NULL);
	if (fill_cmd_array(res, args))
		return (NULL);
	return (res);
}

// char	**combine_cmdline(t_cmd_element *args)
// {
// 	char			**res;
// 	int				count;
// 	int				i;
// 	t_cmd_element	*tmp;

// 	count = count_cmd_element(args);
// 	if (count == 0)
// 		return (NULL);
// 	res = malloc(sizeof(char *) * (count + 1));
// 	i = 0;
// 	tmp = args;
// 	while (tmp)
// 	{
// 		res[i] = ft_strdup(tmp->content);
// 		if (!res[i])
// 		{
// 			while (i--)
// 				free(res[i]);
// 			free(res);
// 			return (NULL);
// 		}
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	res[i] = NULL;
// 	return (res);
// }

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

	minishell_env = prepare_env_and_args(tree, data, &args);
	if (!minishell_env)
		return (1);
	check = prepare_exec(args, &paths, minishell_env);
	if (check)
		return (127);
	execve(paths, args, minishell_env);
	perror("execve failed");
	close_save_fd(data->ast);
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
