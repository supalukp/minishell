/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:06 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/20 12:37:49 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	pipe_no_args(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line) - 1;
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (i == 0 || i == len)
				return (1);
			else
			{
				i++;
				while (line[i] == ' ')
					i++;
				if (line[i] == '\0')
					return (0);
				else if (line[i] == '|')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_semi(char *line)
{
	int		i;
	char	**split;

	i = 0;
	if (ft_strchr(line, ';') == 0)
		return (0);
	if (line[i] == ';' || line[ft_strlen(line) - 1] == ';')
		return (1);
	split = ft_split(line, ';');
	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], '\"'))
			i++;
		else
		{
			free_matrix(split);
			return (1);
		}
	}
	free_matrix(split);
	return (0);
}

int	check_basic_errors(char *line, t_data *data)
{
	if (only_space(line) || only_colon(line))
		return (data->last_exit);
	if (only_exclamation(line))
		return (1);
	if (open_quotes(line))
	{
		stderr_msg("minishell: syntax error: unexpected end of file\n");
		return (2);
	}
	if (pipe_no_args(line))
	{
		stderr_msg("minishell: syntax error near unexpected token '|'\n");
		return (2);
	}
	if (no_files(line))
	{
		stderr_msg("minishell: syntax error near unexpected token 'newline'\n");
		return (2);
	}
	return (-1);
}

int	error_checking(char *line, t_data *data)
{
	int	exit_status;

	exit_status = check_basic_errors(line, data);
	if (exit_status != -1)
		return (exit_status);
	exit_status = check_bracket_error(line);
	if (exit_status != 0)
		return (exit_status);
	if (unsupported_syntax(line))
		return (2);
	return (0);
}

// int	error_checking(char *line, t_data *data)
// {
// 	int	exit_status;
// 	int	bracket;

// 	exit_status = 0;
// 	if (only_space(line) || only_colon(line))
// 		exit_status = data->last_exit;
// 	if (only_exclamation(line))
// 		exit_status = 1;
// 	if (open_quotes(line))
// 	{
// 		stderr_msg("minishell: syntax error: unexpected end of file\n");
// 		return (2);
// 	}
// 	if (pipe_no_args(line))
// 	{
// 		stderr_msg("minishell: syntax error near unexpected token '|'\n");
// 		return (2);
// 	}
// 	if (no_files(line))
// 	{
// 		stderr_msg("minishell: syntax error near unexpected token 'newline'\n");
// 		return (2);
// 	}
// 	bracket = check_bracket(line);
// 	if (bracket == 1)
// 	{
// 		stderr_msg("minishell: open bracket for expansion\n");
// 		return (1);
// 	}
// 	else if (bracket == 2)
// 	{
// 		stderr_msg("minishell: bad substitution\n");
// 		return (1);
// 	}
// 	if (unsupported_syntax(line))
// 		return (2);
// 	return (exit_status);
// }
