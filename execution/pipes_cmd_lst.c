/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:49:02 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/20 12:02:29 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static t_pipe_cmds	*create_pipe_cmd_node(t_tree *token)
{
	t_pipe_cmds	*node;

	node = malloc(sizeof(t_pipe_cmds));
	if (!node)
		return (NULL);
	node->cmd = token;
	node->next = NULL;
	return (node);
}

static void	ft_lstadd_cmd_front(t_pipe_cmds **lst, t_pipe_cmds *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

t_pipe_cmds	*create_cmd_lst(t_tree *tree, t_data *data)
{
	t_pipe_cmds	*lst;
	t_pipe_cmds	*tmp;

	(void)data;
	lst = NULL;
	if (tree->type != PIPE)
		return (NULL);
	while (tree->type == PIPE)
	{
		tmp = create_pipe_cmd_node(tree->right);
		if (!tmp)
			return (NULL);
		ft_lstadd_cmd_front(&lst, tmp);
		if (tree->left->type != PIPE)
			break ;
		tree = tree->left;
	}
	tmp = create_pipe_cmd_node(tree->left);
	if (!tmp)
		free_cmd_lst(lst);
	ft_lstadd_cmd_front(&lst, tmp);
	return (lst);
}
