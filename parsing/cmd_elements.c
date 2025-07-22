/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:44:08 by syukna            #+#    #+#             */
/*   Updated: 2025/07/22 17:27:44 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	get_element_len(char *line, int quoted)
{
	int		i;
	char	end_letter;

	i = 1;
	if (quoted == 2)
		end_letter = '"';
	else if (quoted == 1)
		end_letter = '\'';
	else
	{
		end_letter = ' ';
		i = 0;
	}
	if (end_letter == ' ')
	{
		while (line[i] && !includedchar(line[i], " '\""))
			i++;
	}
	else
	{
		while (line[i] && line[i] != end_letter)
			i++;
	}
	return (i);
}

static void	define_end_letter(int quoted, char	*end_letter, size_t	*rmlen)
{
	if (quoted == 2)
	{
		*end_letter = '"';
		*rmlen = 1;
	}
	else if (quoted == 1)
	{
		*end_letter = '\'';
		*rmlen = 1;
	}
	else
	{
		*end_letter = ' ';
		*rmlen = 0;
	}
}

static size_t	remove_cmd_element_len(t_tree *cmd_line, int quoted)
{
	size_t	rmlen;
	char	end_letter;
	char	*cc;

	cc = cmd_line->content;
	define_end_letter(quoted, &end_letter, &rmlen);
	if (quoted == 0)
		while (cc[rmlen] && !includedchar(cc[rmlen], " '\""))
			rmlen++;
	else
		while (cc[rmlen] != end_letter && cc[rmlen])
			rmlen++;
	if (cc[rmlen] == end_letter)
		rmlen++;
	while (cc[rmlen] == ' ' && cc[rmlen])
		rmlen++;
	return (rmlen);
}

void	handle_remcmd(char	*rtnstr, t_tree *cmd_line, size_t rmlen, int *error)
{
	int		i;

	i = 0;
	rtnstr = ft_calloc(ft_strlen(cmd_line->content) + 1 - rmlen, sizeof(char));
	if (!rtnstr)
	{
		*error = 1;
		free(cmd_line->content);
		return ;
	}
	while (cmd_line->content[i + rmlen])
	{
		rtnstr[i] = cmd_line->content[rmlen + i];
		i++;
	}
	free(cmd_line->content);
	cmd_line->content = rtnstr;
	split_cmd_elements(cmd_line, error);
}

void	remove_cmd_element(t_tree *cmd_line, int quoted, int *error)
{
	size_t	rmlen;
	char	*rtnstr;

	rtnstr = NULL;
	rmlen = remove_cmd_element_len(cmd_line, quoted);
	if (rmlen >= ft_strlen(cmd_line->content))
	{
		free(cmd_line->content);
		cmd_line->content = NULL;
	}
	else
	{
		handle_remcmd(rtnstr, cmd_line, rmlen, error);
	}
}
