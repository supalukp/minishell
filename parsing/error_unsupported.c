/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_unsupported.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:33:40 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 18:42:48 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	check_unsupported(char *line, int i)
{
	if (line[i] == '(' || line[i] == ')')
	{
		stderr_msg("minishell: syntax error near unexpected token ')'\n");
		return (2);
	}
	else if (line[ft_strlen(line) - 1] == '\\')
	{
		stderr_msg("minishell: syntax error near unexpected token '\\'\n");
		return (2);
	}
	return (0);
}

int	unsupported_syntax(char *line)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (check_semi(line))
	{
		stderr_msg("minishell: syntax error near unexpected token ';'\n");
		return (2);
	}
	while (line[i])
	{
		status = check_unsupported(line, i);
		if (status)
			return (2);
		i++;
	}
	return (0);
}
