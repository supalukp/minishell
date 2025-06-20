/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:45:41 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/20 12:37:54 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	only_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	open_quotes(char *line)
{
	int	i;
	int	single_flag;
	int	double_flag;

	i = 0;
	single_flag = 0;
	double_flag = 0;
	while (line[i])
	{
		if (!single_flag && !double_flag && (line[i] == '\'' || line[i] == '"'))
		{
			single_flag = (line[i] == '\'');
			double_flag = (line[i] == '"');
		}
		else if (line[i] == '\'' && single_flag && !double_flag)
			single_flag = 0;
		else if (line[i] == '"' && double_flag && !single_flag)
			double_flag = 0;
		i++;
	}
	return (single_flag || double_flag);
}

int	no_files(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>'
					&& line[i + 1] == '>'))
				i += 2;
			else
				i += 1;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			if (line[i] == '\0' || line[i] == '<' || line[i] == '>'
				|| line[i] == '|' || line[i] == '&')
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	only_colon(const char *line)
{
	if (ft_strlen(line) == 1)
	{
		if (line[0] == ':')
			return (1);
	}
	return (0);
}

int	only_exclamation(const char *line)
{
	if (ft_strlen(line) == 1)
	{
		if (line[0] == '!')
			return (1);
	}
	return (0);
}
