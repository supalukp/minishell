/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:10:05 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/17 23:22:52 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	exec_cmd_line(t_tree *tree, t_data *data, int exit_status)
{
	if (tree->cmd_line == NULL)
		return (0);
	if (is_buildin(tree) == true)
	{
		if (tree->files)
			if (redirect_one_cmd(tree) == -1)
				return (1);
		exit_status = exec_buildin(tree, data);
	}
	else if (tree->left == NULL && tree->right == NULL)
		exit_status = external_single(tree, data);
	else
		exit_status = external_cmd_process(tree, data);
	return (exit_status);
}

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
	return (exit_status);
}

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

char	**combine_cmdline(t_cmd_element *args)
{
	char			**res;
	int				count;
	int				i;
	t_cmd_element	*tmp;

	count = count_cmd_element(args);
	if (count == 0)
		return (NULL);
	res = malloc(sizeof(char *) * (count + 1));
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
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	external_cmd_process(t_tree *tree, t_data *data)
{
	char	**args;
	char	*paths;
	char	**minishell_env;
	int check;
	
	args = combine_cmdline(tree->cmd_line);
	if (!args)
		return (1);
	minishell_env = convert_env_lst_double_arrays(data->env);
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		check = prepare_exec_path(args, &paths, minishell_env);
		if (check)
		{
			// if (minishell_env)
			// 	free_matrix(minishell_env);
			return (127);
		}
	}
	else 
	{
		if (init_path(&paths, args, minishell_env))
		{
			// free_program(data);
			return (127);
		}
	}
	execve(paths, args, minishell_env);
	perror("execve failed");
	close_save_fd(data->ast);
	free_matrix(minishell_env);
	free_matrix(args);
	free(paths);
	return (126);
}
