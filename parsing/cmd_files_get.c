/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_files_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:25:45 by syukna            #+#    #+#             */
/*   Updated: 2025/06/18 19:46:57 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	get_new_redirectionless_str(int index, t_tree *cmd_line)
{
	int		i;
	char	*cc;

	i = 0;
	cc = cmd_line->content;
	while (is_letters(cc[index + i], "< >"))
		i++;
	while (cc[index + i] != '\0' && cc[index + i] != ' ')
		i++;
	return (i);
}

void	remove_redirection(int index, t_tree *cmd_line, int *error)
{
	int		lenrem;
	char	*replacement;
	int		i;

	lenrem = get_new_redirectionless_str(index, cmd_line);
	replacement = ft_calloc(ft_strlen(cmd_line->content) - lenrem + 1, 1);
	if (!replacement)
	{
		free(cmd_line->content);
		*error = 1;
		return ;
	}
	i = 0;
	while (i < index)
	{
		replacement[i] = cmd_line->content[i];
		i++;
	}
	while (cmd_line->content[i + lenrem])
	{
		replacement[i] = cmd_line->content[i + lenrem];
		i++;
	}
	free(cmd_line->content);
	cmd_line->content = replacement;
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

void	redirection_state(t_tree *cmd_line, bool *s_quote, bool *d_quote, int i)
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
		redirection_state(cmd_line, &s_quote, &d_quote, i);
		if (cmd_line->content[i] == '<' || cmd_line->content[i] == '>')
		{
			if (s_quote == false && d_quote == false)
			{
				get_redirections(i, cmd_line, error);
				if (*error)
					return ;
				i = 0;
			}
		}
		else
			i++;
	}
}
