/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exp_tild.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:37:08 by syukna            #+#    #+#             */
/*   Updated: 2025/07/22 17:30:50 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static void	exchange_tild(t_cmd_element *el, char *new, int i, int len)
{
	char	*rtnstr;
	int		j;
	int		y;

	j = 0;
	y = 0;
	rtnstr = ft_calloc(len + 1, sizeof(char));
	while (j < i)
	{
		rtnstr[j] = el->content[j];
		j++;
	}
	while (new[y])
		rtnstr[j++] = new[y++];
	i++;
	while (el->content[i])
		rtnstr[j++] = el->content[i++];
	free(el->content);
	el->content = rtnstr;
}

static void	tild_logic(t_cmd_element *element, char *rtnvalue, int len)
{
	int		i;
	char	*ec;

	i = 0;
	ec = element->content;
	if (ec[i] == '~')
	{
		if (ec[i + 1] && includedchar(ec[i + 1], "/"))
			exchange_tild(element, rtnvalue, i, len);
		else if (!ec[i + 1])
			exchange_tild(element, rtnvalue, i, len);
	}
	else
	{
		while (ec[i] != '~')
			i++;
		if (ec[i - 1] == '=')
		{
			if (!ec[i + 1])
				exchange_tild(element, rtnvalue, i, len);
			else if (ec[i + 1] == '/')
				exchange_tild(element, rtnvalue, i, len);
		}
	}
}

void	add_tild(t_cmd_element *element, t_env *lst)
{
	char	*rtnvalue;
	int		len;

	rtnvalue = find_expansion_match("HOME", lst);
	if (!rtnvalue)
		return ;
	if (includedchar('~', element->content) && element->quoted == 0)
	{
		len = ft_strlen(element->content) + ft_strlen(rtnvalue);
		tild_logic(element, rtnvalue, len);
	}
}
