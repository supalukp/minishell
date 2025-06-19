/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:06 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 16:43:03 by spunyapr         ###   ########.fr       */
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
		if ((line[i] == '\'' || line[i] == '"') && (single_flag == 0
				&& double_flag == 0))
		{
			if (line[i] == '\'')
				single_flag = 1;
			else if (line[i] == '"')
				double_flag = 1;
		}
		else if (line[i] == '\'' && single_flag == 1 && double_flag == 0)
			single_flag = 0;
		else if (line[i] == '"' && double_flag == 1 && single_flag == 0)
			double_flag = 0;
		i++;
	}
	if (single_flag || double_flag)
		return (1);
	return (0);
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
				if (line[i] == '|')
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
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], '\"'))
			i++;
		else
			return (1);
	}
	return (0);
}

int	unsupported_syntax(char *line)
{
	int	i;

	i = 0;
	if (check_semi(line))
	{
		stderr_msg("minishell: syntax error near unexpected token ';'\n");
		return (2);
	}
	while (line[i])
	{
		if (line[i] == '(' || line[i] == ')')
		{
			stderr_msg("minishell: syntax error near unexpected token ')'\n");
			return (2);
		}
		if (line[i] == '&' && line[i + 1] != '&')
		{
			stderr_msg("minishell: syntax error near unexpected token '&'\n");
			return (2);
		}
		else if (line[i] == '&' && line[i + 1] == '&')
		{
			stderr_msg("minishell: syntax error near unexpected token '&&'\n");
			return (2);
		}
		else if (line[ft_strlen(line) - 1] == '\\')
		{
			stderr_msg("minishell: syntax error near unexpected token '\\'\n");
			return (2);
		}
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

int	error_checking(char *line, t_data *data)
{
	int	exit_status;
	int	bracket;

	exit_status = 0;
	if (only_space(line) || only_colon(line))
		exit_status = data->last_exit;
	if (only_exclamation(line))
		exit_status = 1;
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
	bracket = check_bracket(line);
	if (bracket == 1)
	{
		stderr_msg("minishell: open bracket for expansion\n");
		return (1);
	}
	else if (bracket == 2)
	{
		stderr_msg("minishell: bad substitution\n");
		return (1);
	}
	if (unsupported_syntax(line))
		return (2);
	return (exit_status);
}
