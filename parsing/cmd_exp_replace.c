/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exp_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:14:52 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 18:19:06 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	expansion_logic(int *i, t_cmd_element *line, int *sl, int *count)
{
	int		j;
	char	*lc;

	j = 0;
	lc = line->content;
	if (!line->content[*i + 1] || line->content[*i + 1] == ' ')
		(*count)++;
	if (*i > 0 && line->content[*i - 1] == '\\')
	{
		*sl = 1;
		(*count)++;
		ft_memmove(&lc[*i - 1], &lc[*i], ft_strlen(&lc[*i]) + 1);
		(*i)--;
	}
	else if (line->content[*i + 1] == '{')
	{
		line->expand_curly_brackets = 2;
		ft_memmove(&lc[*i + 1], &lc[*i + 2], ft_strlen(&lc[*i + 2]) + 1);
	}
	(*i)++;
	while (ft_isalnum(line->content[*i + j]) || line->content[*i + j] == '_')
		j++;
	return (j);
}

static void	handle_exp(t_cmd_element *l, t_env *lst, int i, int packed)
{
	char	*searchword;
	char	*rtnvalue;
	int		j;
	int		slashed;

	j = packed / 100;
	slashed = packed % 100;
	searchword = ft_calloc(j + 1, sizeof(char));
	if (!searchword)
		return ;
	ft_strlcpy(searchword, &l->content[i], j + 1);
	rtnvalue = find_expansion_match(searchword, lst);
	free(searchword);
	i--;
	if (slashed != 1 && rtnvalue)
		exchange_expansion_values(l, rtnvalue, i, ft_strlen(l->content) - j
			+ ft_strlen(rtnvalue));
	else
	{
		exchange_expansion_values(l, "", i, ft_strlen(l->content) - j);
	}
}

void	replace_expansion(t_cmd_element *l, t_env *lst, int *count)
{
	int	i;
	int	j;
	int	slashed;

	slashed = 0;
	i = current_pos_dollar(l->content, *count);
	if (i == -1 || *count >= counterchar(l->content, '$'))
		return ;
	if (l->content[i + 1] && includedchar(l->content[i + 1], "? "))
	{
		if (l->content[i + 1] == ' ')
			(*count)++;
		return ;
	}
	if (!l->content[i + 1] || !ft_isalpha(l->content[i + 1]))
	{
		(*count)++;
		return ;
	}
	j = expansion_logic(&i, l, &slashed, count);
	handle_exp(l, lst, i, j * 100 + slashed);
}
