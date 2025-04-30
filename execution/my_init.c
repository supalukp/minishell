/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:26:23 by spunyapr          #+#    #+#             */
/*   Updated: 2025/04/29 17:44:30 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headings.h"

void pipe_simple_input(t_token *tree)
{
    // cmd = ls -al | wc -l  
    tree->type = PIPE;
    tree->name = "|";
    
    // Left    
    tree->left = malloc(sizeof(t_token));
    tree->left->type = CMD;
    tree->left->name = "ls -al";
    tree->left->left = NULL;
    tree->left->right = NULL;

    // Right
    tree->right = malloc(sizeof(t_token));
    tree->right->type = CMD;
    tree->right->name = "wc -l";
    tree->right->left = NULL;
    tree->right->right = NULL;
}

void pipe_double_input(t_token *tree)
{
    // cmd = ls -al | wc -l | cat -e
    tree->type = PIPE;
    tree->name = "|";
    
    // TREE-RIGHT
    tree->right = malloc(sizeof(t_token));
    tree->right->type = CMD;
    tree->right->name = "cat -e";
    tree->right->left = NULL;
    tree->right->right = NULL;
    
    // TREE-LEFT
    tree->left = malloc(sizeof(t_token));
    tree->left->type = PIPE;
    tree->left->name = "|";
    
    // TREE-LEFT Left    
    tree->left->left->type = CMD;
    tree->left->left->name = "ls -al";
    tree->left->left->left = NULL;
    tree->left->left->right = NULL;

    // TREE-LEFT Right
    tree->left->right = malloc(sizeof(t_token));
    tree->left->right->type = CMD;
    tree->left->right->name = "wc -l";
    tree->left->right->left = NULL;
    tree->left->right->right = NULL;
}
