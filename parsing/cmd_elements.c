/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:44:08 by syukna            #+#    #+#             */
/*   Updated: 2025/06/14 15:17:16 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	get_element_len(char *line, int quoted)
{
	int i;
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
		while(line[i] && !includedchar(line[i], " '\""))
			i++;
	}
	else
	{
		while (line[i] && line[i] != end_letter)
			i++;
	}
	if (quoted)
		i--;
	return (i);
}

char	*get_element(char *line, int quoted, int len)
{
	char	*rtnstr;
	int		i;
	int		j;
	
	i = 0;
	if (quoted >= 1)
		j = 1;
	else
		j = 0;
	rtnstr = ft_calloc(len + 1, sizeof(char));
	if (!rtnstr)
		return (NULL);
	while (i < len)
	{
		rtnstr[i] = line[i + j];
		i++;
	}
	return (rtnstr);
}
size_t	remove_cmd_element_len(t_tree *cmd_line, int quoted)
{
	size_t	rmlen;
	char	end_letter;

	if (quoted == 2)
	{
		end_letter = '"';
		rmlen = 1;
	}
	else if (quoted == 1)
	{
		end_letter = '\'';
		rmlen = 1;
	}
	else
	{
		end_letter = ' ';
		rmlen = 0;
	}
	if (quoted == 0)
		while(cmd_line->content[rmlen] && !includedchar(cmd_line->content[rmlen], " '\""))
			rmlen++;
	else
		while (cmd_line->content[rmlen] != end_letter && cmd_line->content[rmlen])
			rmlen++;
	if (cmd_line->content[rmlen] == end_letter)
		rmlen++;
	while (cmd_line->content[rmlen] == ' ' && cmd_line->content[rmlen])
		rmlen++;
	return (rmlen);
}

void	remove_cmd_element(t_tree *cmd_line, int quoted, int *error)
{
	size_t rmlen;
	int i;
	char	*rtnstr;

	i = 0;
	rmlen = remove_cmd_element_len(cmd_line, quoted);
	if (rmlen >= ft_strlen(cmd_line->content))
	{
		free(cmd_line->content);
		cmd_line->content = NULL;
	}
	else 
	{
		rtnstr = ft_calloc(ft_strlen(cmd_line->content) + 1 - rmlen , sizeof(char));
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
}

void	add_cmd_element(t_tree *cmd_line, int quoted, int len, int *error)
{
	t_cmd_element	*element;
	t_cmd_element	*eltmp;
	int				gap;

	element = ft_calloc(1, sizeof(t_cmd_element));
	if (!element)
	{
		*error = 1;
		return ;
	}
	if (quoted >= 1)
		gap = 2;
	else
		gap = 0;
	element->quoted = quoted;
	element->content = get_element(cmd_line->content, quoted, len);
	if (cmd_line->content[len + gap] && cmd_line->content[len + gap] != ' ')
		element->space_after = 0;
	else
		element->space_after = 1;
	if (!element->content)
	{
		*error = 1;
		return ;
	}
	if (!cmd_line->cmd_line)
		cmd_line->cmd_line = element;
	else
	{
		eltmp = cmd_line->cmd_line;
		while (eltmp->next)
			eltmp = eltmp->next;
		eltmp->next = element;
	}
}

void	handle_cmd_element(t_tree *cmd_line, int quoted, int *error)
{
	int len;

	len = get_element_len(cmd_line->content, quoted);
	add_cmd_element(cmd_line, quoted, len, error);
	remove_cmd_element(cmd_line, quoted, error);
	// if (error && cmd_line->cmd_line)
	// 	free(cmd_line->cmd_line);
}

void	split_cmd_elements(t_tree *cmd_line, int *error)
{
	int i;
	char *tmpstr;

	i = 0;
	tmpstr = ft_strtrim(cmd_line->content, " ");
	free(cmd_line->content);
	cmd_line->content = tmpstr;
	if (tmpstr[i])
	{
		if (tmpstr[i] == '"')
			handle_cmd_element(cmd_line, 2, error);
		else if (tmpstr[i] == '\'')
			handle_cmd_element(cmd_line, 1, error);
		else
			handle_cmd_element(cmd_line, 0, error);
	}
}
