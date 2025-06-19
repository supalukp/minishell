/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:05:15 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 14:51:54 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

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
	redirect_status = exec_builtin(tree, data);
	backup_std_io(stdin_backup, stdout_backup);
	return (redirect_status);
}

int	exec_cmd_line(t_tree *tree, t_data *data, int exit_status)
{
	if (tree->cmd_line == NULL && tree->files)
		exit_status = external_single(tree, data);
	else if (is_builtin(tree))
	{
		return (execute_builtin_with_redirects(tree, data));
	}
	else if (!tree->left && !tree->right)
		exit_status = external_single(tree, data);
	else if (tree->left && tree->right)
		exit_status = external_cmd_process(tree, data);
	else
		return (0);
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
