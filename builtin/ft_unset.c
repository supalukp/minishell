/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:48:52 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/03 15:18:25 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int unset_process(t_tree_token *tree, t_data *data)
{
	int				flag;
	t_cmd_element	*args;

	flag = 0;
	args = tree->cmd_line->next;
	while (args)
	{
		if (invalid_option(args, "unset"))
			return (2);
		else if ()
	}
		
}


int ft_unset(t_tree_token *tree, t_data *data)
{
	if (no_argument(tree))
		return (0);
	else
		return (unset_process());
}