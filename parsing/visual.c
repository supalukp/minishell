/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:30:04 by syukna            #+#    #+#             */
/*   Updated: 2025/05/03 18:21:21 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	print_node(t_token *node)
{
	printf("***************************************************\n");
	printf("* Content: |%s|\n", node->content);
	printf("* Type: %d\n", node->type);
	if (node->left)
	{
		if (node->left->type == CMD)
			printf("* Left link: %s\n", node->left->content);
		else
			printf("* Left link: Operator type %d\n", node->left->type);
	}
	if (node->right)
	{
		if (node->right->type == CMD)
			printf("* right link: %s\n", node->right->content);
		else
			printf("* right link: Operator type %d\n", node->right->type);
	}
	printf("***************************************************\n\n");
}