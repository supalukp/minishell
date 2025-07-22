/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_elements_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:56:55 by syukna            #+#    #+#             */
/*   Updated: 2025/07/22 17:55:17 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static char	*get_element(char *line, int quoted, int len)
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

static void	handle_ele(t_tree *cl, t_cmd_element *element, int len, int gap)
{
	t_cmd_element	*eltmp;

	if (cl->content[len + gap] && cl->content[len + gap] != ' ')
		element->space_after = 0;
	else
		element->space_after = 1;
	if (!cl->cmd_line)
		cl->cmd_line = element;
	else
	{
		eltmp = cl->cmd_line;
		while (eltmp->next)
			eltmp = eltmp->next;
		eltmp->next = element;
	}
}

static void	add_cmd_element(t_tree *cmd_line, int quoted, int len, int *error)
{
	t_cmd_element	*element;
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
	if (!element->content)
	{
		*error = 1;
		return ;
	}
	handle_ele(cmd_line, element, len, gap);
}

static void	handle_cmd_element(t_tree *cmd_line, int quoted, int *error)
{
	int	len;

	len = get_element_len(cmd_line->content, quoted);
	if (quoted)
		len--;
	add_cmd_element(cmd_line, quoted, len, error);
	remove_cmd_element(cmd_line, quoted, error);
}

void	split_cmd_elements(t_tree *cmd_line, int *error)
{
	int		i;
	char	*tmpstr;

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
