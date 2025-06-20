/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:00:22 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/20 12:20:55 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	ft_env(t_tree *tree, t_data *data)
{
	if (!data->env)
		return (0);
	if (!no_argument(tree))
	{
		if (tree->cmd_line->next->content[0] == '-')
		{
			ft_putstr_fd("env: invalid option\n", 2);
			return (125);
		}
		else
		{
			ft_putstr_fd("env: invalid agrument\n", 2);
			return (127);
		}
	}
	print_env(data->env);
	return (0);
}
