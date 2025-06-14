/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:25:45 by syukna            #+#    #+#             */
/*   Updated: 2025/06/14 12:35:27 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int		get_new_redirectionless_str(int index, t_tree *cmd_line)
{
	int	i;
	
	i = 0;
	while(is_letters(cmd_line->content[index + i],"< >"))
		i++;
	while (cmd_line->content[index + i] != '\0' && cmd_line->content[index + i] != ' ')
		i++;
	return (i);
}

void	remove_redirection(int index, t_tree *cmd_line, int *error)
{
	int lenrem;
	char *replacement;
	int	i;
	
	lenrem = get_new_redirectionless_str(index, cmd_line);
	replacement = ft_calloc(ft_strlen(cmd_line->content) - lenrem + 1, sizeof(char));
	if (!replacement)
	{
		free(cmd_line->content);
		*error = 1;
		return ; \
	}
	i = 0;
	while (i < index)
	{
		replacement[i] = cmd_line->content[i];
		i++;
	}
	while (cmd_line->content[i + lenrem])
	{
		replacement[i] = cmd_line->content[i  + lenrem];
		i++;
	}
	free(cmd_line->content);
	cmd_line->content = replacement;
}

char	*get_redirection_file(int index, char *cmd_line, int *error)
{
	int i;
	int j;
	char *file_name;
	
	i = 0;
	j = 0;
	while(cmd_line[i + index] == ' ')
		index++;
	while ( cmd_line[i + index] != ' ' && cmd_line[i + index] != '\0')
		i++;
	file_name = ft_calloc(i + 1, sizeof(char));
	if (!file_name)
	{
		free(cmd_line);
		return (*error = 1, NULL); // TODO exit
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

// INFILE, <
// HEREDOC, <<
// OUTFILE, >
// OUTFILE_APPEND, >>

void	get_redirections(int index, t_tree *cmd_line, int *error)
{
	int 	i;
	char	*filename;
	t_type	filetype;

	if (!cmd_line || !cmd_line->content || *error)
		return;
	i = index;
	filetype = define_redirection_type(i, cmd_line->content);
	while(is_letters(cmd_line->content[i],"< >"))
		i++;
	filename = get_redirection_file(i, cmd_line->content, error);
	if (!filename)
	{
		*error = 1;
		return;
	}
	remove_redirection(index, cmd_line, error);
	if (*error)
	{
		free(filename);
		return;
	}
	add_cmd_file(filename, filetype, cmd_line, error);
}

void	identify_redirections(t_tree *cmd_line, int *error)
{
	size_t	i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = false;
	d_quote = false;
	while (cmd_line->content[i])
	{
		if (*error)
			return ;
		if (cmd_line->content[i] == '\'')
		{
			if (s_quote == false)
				s_quote = true;
			else
				s_quote = false;
		}
		if (cmd_line->content[i] == '\"')
		{
			if (d_quote == false)
				d_quote = true;
			else
				d_quote = false;
		}
		if ((cmd_line->content[i] == '<' || cmd_line->content[i] == '>') && s_quote == false && d_quote == false)
		{
			get_redirections(i, cmd_line, error);
			if (*error)
				return ;
			i = 0;
		}
		else
			i++;
	}
}
