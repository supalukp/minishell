/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_spec_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:04:06 by syukna            #+#    #+#             */
/*   Updated: 2025/07/17 11:58:41 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

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
}

void	spec_dol(t_cmd_element *line, int *count, int code)
{
	int		i;
	int		len;
	char	*codestr;

	i = current_pos_dollar(line->content, *count);
	if (i == -1)
		return ;
	// printf("line->content %s\n", line->content);
	if (i == 0 && line->content && !line->content[i + 1] && line->next && line->next->quoted)
		line->content[i] = '\0';
	else if (line->content[i + 1] && line->content[i + 1] == '?')
	{
		codestr = ft_itoa(code);
		len = ft_strlen(line->content) - 2 + ft_strlen(codestr);
		exchange_dollar_values(line, codestr, i, len);
		free(codestr);
	}
}
