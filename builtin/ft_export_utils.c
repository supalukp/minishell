/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:48:10 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/04 10:02:09 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

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
