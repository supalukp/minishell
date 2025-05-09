/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:26:23 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/09 17:14:46 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	print_ast(t_tree_token *node)
{
	char **res;
	int i;

	i = 0;
	if (!node)
		return ;
	if (node->type == PIPE)
		printf("PIPE: %s\n", node->content);
	else if (node->type == CMD_LINE)
	{
		res = combine_cmdline(node->cmd_line);
		while (res[i])
		{
			printf("%s ", res[i]);
			if (!res[i + 1])
			printf("\n");
			i++;
		}
		free_matrix(res);
	}
	print_ast(node->left);
	print_ast(node->right);
}

void	free_ast(t_tree_token **node)
{
	t_tree_token	*tmp_left;
	t_tree_token	*tmp_right;
	t_cmd_element *tmp_cmd;
	t_cmd_element *next;

	if (!(*node))
		return ;
	tmp_left = (*node)->left;
	tmp_right = (*node)->right;
	if (tmp_left)
		free_ast(&tmp_left);
	if (tmp_right)
		free_ast(&tmp_right);
	if ((*node)->content)
		free((*node)->content);
	if ((*node)->cmd_line)
	{
		tmp_cmd = (*node)->cmd_line;
		while (tmp_cmd)
		{
			next = tmp_cmd->next;
			free(tmp_cmd->content);
			free(tmp_cmd);
			tmp_cmd = next;
		}
	}
	if ((*node))
		free((*node));
}



void init_s_main(t_data **data, t_tree_token *tree)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return;
	(*data)->ast = tree;
	(*data)->env = NULL;	
}


void one_cmd(t_tree_token **tree)
{
	(*tree) = malloc(sizeof(t_tree_token));
	(*tree)->type = CMD_LINE;
	(*tree)->content = ft_strdup("ls -al > infile");
	(*tree)->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->cmd_line->content = ft_strdup("echo");
	(*tree)->cmd_line->quoted = 0;
	(*tree)->cmd_line->type = CMD;
	(*tree)->cmd_line->next = malloc(sizeof(t_cmd_element));
	(*tree)->cmd_line->next->content = ft_strdup("\"hello\"");
	(*tree)->cmd_line->next->type = ARG;
	(*tree)->cmd_line->next->next = NULL;
	(*tree)->infiles = NULL;
	(*tree)->outfiles = NULL;
	(*tree)->left = NULL;
	(*tree)->right = NULL;
}

void	pipe_simple_input(t_tree_token **tree)
{
	(*tree) = malloc(sizeof(t_tree_token));
	(*tree)->type = PIPE;
	(*tree)->content = ft_strdup("|");
	(*tree)->cmd_line = NULL;
	(*tree)->infiles = NULL;
	(*tree)->outfiles = NULL;
	
	(*tree)->left = malloc(sizeof(t_tree_token));
	(*tree)->left->type = CMD_LINE;
	(*tree)->left->content = ft_strdup("echo hello");
	(*tree)->left->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->left->cmd_line->content = ft_strdup("echo");
	(*tree)->left->cmd_line->quoted = 0;
	(*tree)->left->cmd_line->type = CMD;
	(*tree)->left->cmd_line->next = malloc(sizeof(t_cmd_element));
	(*tree)->left->cmd_line->next->content = ft_strdup("\"hello\"");
	(*tree)->left->cmd_line->next->type = ARG;
	(*tree)->left->cmd_line->next->next = NULL;
	(*tree)->left->left = NULL;
	(*tree)->left->right = NULL;
	(*tree)->left->infiles = NULL;
	(*tree)->left->outfiles = NULL;

	(*tree)->right = malloc(sizeof(t_tree_token));
	(*tree)->right->type = CMD_LINE;
	(*tree)->right->content = ft_strdup("rev");
	(*tree)->right->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->right->cmd_line->content = ft_strdup("rev");
	(*tree)->right->cmd_line->quoted = 0;
	(*tree)->right->cmd_line->type = CMD;
	(*tree)->right->cmd_line->next = NULL;
	(*tree)->right->left = NULL;
	(*tree)->right->right = NULL;
	(*tree)->right->infiles = NULL;
	(*tree)->right->outfiles = NULL;
}
