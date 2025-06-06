/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:20:35 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/06 15:27:49 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	free_file_list(t_file *file)
{
	t_file	*tmp;

	while (file)
	{
		tmp = file->next;
		if (file->content)
			free(file->content);
		free(file);
		file = tmp;
	}
}

void	free_ast(t_tree *node)
{
	t_cmd_element	*tmp_cmd;
	t_cmd_element	*next;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->content)
		free(node->content);
	tmp_cmd = node->cmd_line;
	while (tmp_cmd)
	{
		next = tmp_cmd->next;
		if (tmp_cmd->content)
			free(tmp_cmd->content);
		free(tmp_cmd);
		tmp_cmd = next;
	}
	if (node->files)
		free_file_list(node->files);
	free(node);
}

void	init_s_main(t_data **data, t_tree *tree, char **env)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return ;
	(*data)->ast = tree;
	(*data)->env = env_init(env);
	(*data)->last_exit = 0;
}

// void	print_ast(t_tree *node)
// {
// 	char	**res;
// 	t_file	*file;
// 	int		i;

// 	i = 0;
// 	if (!node)
// 		return ;
// 	if (node->type == PIPE)
// 		printf("PIPE: %s\n", node->content);
// 	else if (node->type == CMD_LINE)
// 	{
// 		res = combine_cmdline(node->cmd_line);
// 		while (res[i])
// 		{
// 			printf("%s ", res[i]);
// 			if (!res[i + 1])
// 				printf("\n");
// 			i++;
// 		}
// 		free_matrix(res);
// 		file = node->files;
// 		while (file)
// 		{
// 			printf("file = %s\n", file->content);
// 			file = file->next;
// 		}
// 	}
// 	print_ast(node->left);
// 	print_ast(node->right);
// }
