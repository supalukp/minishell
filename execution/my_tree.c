/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:26:23 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/06 11:21:49 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	print_ast(t_token *node)
{
	if (!node)
		return ;
	if (node->type == PIPE)
		printf("PIPE: %s\n", node->name);
	else if (node->type == CMD)
		printf("CMD: %s\n", node->name);
	print_ast(node->left);
	print_ast(node->right);
}

void	free_ast(t_token **node)
{
	t_token	*tmp_left;
	t_token	*tmp_right;

	if (!(*node))
		return ;
	tmp_left = (*node)->left;
	tmp_right = (*node)->right;
	if ((&(*node)->left) != NULL)
		free_ast(&(*node)->left);
	if ((&(*node)->right) != NULL)
		free_ast(&(*node)->right);
	free((*node)->name);
	free((*node));
}

void one_cmd(t_token **tree)
{
	(*tree) = malloc(sizeof(t_token));
	(*tree)->type = CMD;
	(*tree)->name = ft_strdup("pwd");
	(*tree)->left = NULL;
	(*tree)->right = NULL;
}

void	pipe_simple_input(t_token **tree)
{
	// cmd = ls -al | wc -l
	(*tree) = malloc(sizeof(t_token));
	(*tree)->type = PIPE;
	(*tree)->name = ft_strdup("|");
	// Left
	(*tree)->left = malloc(sizeof(t_token));
	(*tree)->left->type = CMD;
	(*tree)->left->name = ft_strdup("pwd");
	(*tree)->left->left = NULL;
	(*tree)->left->right = NULL;
	// Right
	(*tree)->right = malloc(sizeof(t_token));
	(*tree)->right->type = CMD;
	(*tree)->right->name = ft_strdup("cat");
	(*tree)->right->left = NULL;
	(*tree)->right->right = NULL;
}

void	pipe_double_input(t_token **tree)
{
	// cmd = ls -al | wc -l | cat -e
	(*tree) = malloc(sizeof(t_token));
	(*tree)->type = PIPE;
	(*tree)->name = ft_strdup("|");
	// TREE-RIGHT
	(*tree)->right = malloc(sizeof(t_token));
	(*tree)->right->type = CMD;
	(*tree)->right->name = "rev";
	(*tree)->right->left = NULL;
	(*tree)->right->right = NULL;
	// TREE-LEFT
	(*tree)->left = malloc(sizeof(t_token));
	(*tree)->left->type = PIPE;
	(*tree)->left->name = ft_strdup("|");
	// TREE-LEFT Left
	(*tree)->left->left = malloc(sizeof(t_token));
	(*tree)->left->left->type = CMD;
	(*tree)->left->left->name = ft_strdup("ls -al");
	(*tree)->left->left->left = NULL;
	(*tree)->left->left->right = NULL;
	// TREE-LEFT Right
	(*tree)->left->right = malloc(sizeof(t_token));
	(*tree)->left->right->type = CMD;
	(*tree)->left->right->name = ft_strdup("wc -l");
	(*tree)->left->right->left = NULL;
	(*tree)->left->right->right = NULL;
}

void	pipe_triple_input(t_token **tree)
{
	// cmd = ls -al | wc -l | cat -e | rev
	(*tree) = malloc(sizeof(t_token));
	(*tree)->type = PIPE;
	(*tree)->name = ft_strdup("|");

	// TREE-RIGHT
	(*tree)->right = malloc(sizeof(t_token));
	(*tree)->right->type = CMD;
	(*tree)->right->name = "rev";
	(*tree)->right->left = NULL;
	(*tree)->right->right = NULL;

	// TREE-LEFT
	(*tree)->left = malloc(sizeof(t_token));
	(*tree)->left->type = PIPE;
	(*tree)->left->name = ft_strdup("|");

	// TREE-LEFT Left
	(*tree)->left->left = malloc(sizeof(t_token));
	(*tree)->left->left->type = PIPE;
	(*tree)->left->left->name = ft_strdup("|");

	// TREE-LEFT Left Left
	(*tree)->left->left->left = malloc(sizeof(t_token));
	(*tree)->left->left->left->type = CMD;
	(*tree)->left->left->left->name = ft_strdup("ls -al");
	(*tree)->left->left->left->left = NULL;
	(*tree)->left->left->left->right = NULL;

	// TREE-LEFT Left Right
	(*tree)->left->left->right = malloc(sizeof(t_token));
	(*tree)->left->left->right->type = CMD;
	(*tree)->left->left->right->name = ft_strdup("wc -l");
	(*tree)->left->left->right->left = NULL;
	(*tree)->left->left->right->right = NULL;

	// TREE-LEFT Right
	(*tree)->left->right = malloc(sizeof(t_token));
	(*tree)->left->right->type = CMD;
	(*tree)->left->right->name = ft_strdup("cat -e");
	(*tree)->left->right->left = NULL;
	(*tree)->left->right->right = NULL;
}