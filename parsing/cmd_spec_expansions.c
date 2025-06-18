/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_spec_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:04:06 by syukna            #+#    #+#             */
/*   Updated: 2025/06/17 18:43:35 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	exchange_tild(t_cmd_element *el, char *new, int i, int len)
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

void	add_tild(t_cmd_element *element, t_env *lst)
{
	(void)lst;
	int	i;
	char	*rtnvalue;
	int		len;

	i = 0;
	rtnvalue = find_expansion_match("HOME",lst);
	if (!rtnvalue)
	return ;
	if (includedchar('~', element->content) && element->quoted == 0)
	{
		len = ft_strlen(element->content) + ft_strlen(rtnvalue);
		if (element->content[i] == '~')
		{
			if (element->content[i + 1] && includedchar(element->content[i + 1], "/"))
				exchange_tild(element, rtnvalue, i, len);
			else if (!element->content[i + 1])
				exchange_tild(element, rtnvalue, i, len);
		}
		else
		{
			while (element->content[i] != '~')
				i++;
			if (element->content[i - 1] == '=')
			{
				if (!element->content[i + 1])
					exchange_tild(element, rtnvalue, i, len);
				else if (element->content[i + 1] == '/')
					exchange_tild(element, rtnvalue, i, len);
			}
		}
	}
}

void	exchange_dollar_values(t_cmd_element *el, char *new, int i, int len)
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
	i += 2;
	while (el->content[i])
		rtnstr[j++] = el->content[i++];
	free(el->content);
	el->content = rtnstr;
	printf("rtnstr = %s\n", el->content);
}

void	special_dollar_sign(t_cmd_element *line, t_env *lst, int *count, int exit_code)
{
	int i;
	int len;
	char	*codestr;
	char	*pid;

	i = current_pos_dollar(line->content, *count);
	if (i == -1)
		return ;
	(void)lst;

	if (line->content[i + 1] && line->content[i + 1] == '?')
	{
		codestr = ft_itoa(exit_code);
		len = ft_strlen(line->content) - 2 + ft_strlen(codestr);
		exchange_dollar_values(line, codestr, i, len);
		free(codestr);
	}
	else if (line->content[i + 1] && line->content[i + 1] == '$')
	{
		pid = ft_itoa(getpid());
		len = ft_strlen(line->content) - 2 + ft_strlen(pid);
		exchange_dollar_values(line, pid, i, len);
		free(pid);
	}
}
