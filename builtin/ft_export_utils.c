/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:48:10 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/03 14:22:34 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	count_env_node(t_env *env_lst)
{
	int	count;

	count = 0;
	while (env_lst)
	{
		count++;
		env_lst = env_lst->next;
	}
	return (count);
}

int	have_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_plus_equal(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '+' && args[i + 1] == '=')
			return (1);
		else if (args[i] == '+' && args[i] != '=')
			return (0);
		i++;
	}
	return (0);
}
