/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:45:41 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 14:36:45 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	check_bracket_open(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '{')
		{
			i += 2;
			if (line[i] == '\0')
				return (1);
			while (line[i] != '}' && line[i])
			{
				i++;
				if (line[i] == '\0')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_bracket(const char *line)
{
	int	i;

	i = 0;
	if (check_bracket_open(line))
		return (1);
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '{')
		{
			i += 2;
			if (line[i] == '}')
				return (2);
			while (line[i] != '}' && line[i])
			{
				if (!ft_isalnum(line[i]) && line[i] != '_')
					return (2);
				i++;
			}
		}
		i++;
	}
	return (0);
}
