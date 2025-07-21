/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:25:45 by syukna            #+#    #+#             */
/*   Updated: 2025/07/21 16:18:26 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

char	*get_redirection_file(int index, char *cmd_line, int *error)
{
	int		i;
	int		j;
	char	*file_name;

	i = 0;
	j = 0;
	while (cmd_line[i + index] == ' ')
		index++;
	while (cmd_line[i + index] != ' ' && cmd_line[i + index] != '\0')
		i++;
	file_name = ft_calloc(i + 1, sizeof(char));
	if (!file_name)
	{
		free(cmd_line);
		return (*error = 1, NULL);
	}
	while (j < i)
	{
		file_name[j] = cmd_line[index + j];
		j++;
	}
	return (file_name);
}

t_type	define_redirection_type(int index, char *cmd_line)
{
	if (cmd_line[index] == '<')
	{
		if (cmd_line[index + 1] == '<')
			return (HEREDOC);
		return (INFILE);
	}
	if (cmd_line[index] == '>')
	{
		if (cmd_line[index + 1] == '>')
			return (APPEND);
		return (OUTFILE);
	}
	return (INVALID);
}

void	get_redirections(int index, t_tree *cmd_line, int *error)
{
	int		i;
	char	*filename;
	t_type	filetype;

	if (!cmd_line || !cmd_line->content || *error)
		return ;
	i = index;
	filetype = define_redirection_type(i, cmd_line->content);
	while (is_letters(cmd_line->content[i], "< >"))
		i++;
	filename = get_redirection_file(i, cmd_line->content, error);
	if (!filename)
	{
		*error = 1;
		return ;
	}
	remove_redirection(index, cmd_line, error);
	if (*error)
	{
		free(filename);
		return ;
	}
	add_cmd_file(filename, filetype, cmd_line, error);
}

void	define_quoted(t_tree *cmd_line, int i, bool *s_quote, bool *d_quote)
{
	if (cmd_line->content[i] == '\'')
	{
		if (*s_quote == false)
			*s_quote = true;
		else
			*s_quote = false;
	}
	if (cmd_line->content[i] == '\"')
	{
		if (*d_quote == false)
			*d_quote = true;
		else
			*d_quote = false;
	}
}

// void	identify_redirections(t_tree *cmd_line, int *error)
// {
// 	size_t	i;
// 	bool	s_quote;
// 	bool	d_quote;

// 	i = 0;
// 	s_quote = false;
// 	d_quote = false;
// 	while (cmd_line->content[i])
// 	{
// 		if (*error)
// 			return ;
// 		define_quoted(cmd_line, i, &s_quote, &d_quote);
// 		if (includedchar(cmd_line->content[i], "<>") && \
// 			s_quote == false && d_quote == false)
// 		{
// 			get_redirections(i, cmd_line, error);
// 			if (*error)
// 				return ;
// 			i = 0;
// 		}
// 		else
// 			i++;
// 	}
// }
