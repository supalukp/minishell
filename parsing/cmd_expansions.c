/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:11:57 by syukna            #+#    #+#             */
/*   Updated: 2025/06/19 22:30:09 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	exchange_expansion_values(t_cmd_element *el, char *new, int i, int len)
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
	while (ft_isalnum(el->content[i]) || el->content[i] == '_')
		i++;
	if (el->expand_curly_brackets == 2 && el->content[i] == '}')
		i++;
	while (el->content[i])
		rtnstr[j++] = el->content[i++];
	free(el->content);
	el->content = rtnstr;
	trim_space(el);
}

int	expansion_logic(int	*i, t_cmd_element *line, int *slashed, int *count)
{
	int		j;
	char	*lc;

	j = 0;
	lc = line->content;
	if (!line->content[*i + 1] || line->content[*i + 1] == ' ')
		(*count)++;
	if (*i > 0 && line->content[*i - 1] == '\\')
	{
		*slashed = 1;
		(*count)++;
		memmove(&lc[*i - 1], &lc[*i], strlen(&lc[*i]) + 1);
		(*i)--;
	}
	else if (line->content[*i + 1] == '{')
	{
		line->expand_curly_brackets = 2;
		memmove(&lc[*i + 1], &lc[*i + 2], strlen(&lc[*i + 2]) + 1);
	}
	(*i)++;
	while (ft_isalnum(line->content[*i + j]) || line->content[*i + j] == '_')
		j++;
	return (j);
}

void	replace_expansion(t_cmd_element *l, t_env *lst, int *count)
{
	int		i;
	int		j;
	int		len;
	char	*searchword;
	char	*rtnvalue;
	int		slashed;

	slashed = 0;
	i = current_pos_dollar(l->content, *count);
	if (i == -1 || *count >= counterchar(l->content, '$'))
		return ;
	if (l->content[i + 1] && includedchar(l->content[i + 1], "$? "))
		return ;
	if (!l->content[i + 1] || ft_isalpha(l->content[i + 1]))
	{
		(*count)++;
		return ;
	}
	j = expansion_logic(&i, l, &slashed, count);
	searchword = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(searchword, &l->content[i], j + 1);
	rtnvalue = find_expansion_match(searchword, lst);
	len = ft_strlen(l->content) - j + ft_strlen(rtnvalue);
	i--;
	free(searchword);
	if (slashed != 1)
		exchange_expansion_values(l, rtnvalue, i, len);
}

int	add_expansions(t_tree *node, t_env *lst, t_data *request)
{
	t_cmd_element	*cmd;
	// int				expansions;
	int				count;
	char			*cc;
	int				q;

	cmd = node->cmd_line;
	count = 0;
	while (cmd)
	{
		add_tild(cmd, lst);
		cc = cmd->content;
		// expansions = counterchar(cc, '$');
		q = cmd->quoted;
		while (includedchar('$', cc) && q != 1 && count < counterchar(cc, '$'))
		{
			spec_dol(cmd, &count, request->last_exit);
			replace_expansion(cmd, lst, &count);
			cc = cmd->content;
		}
		cmd = cmd->next;
		count = 0;
	}
	return (0);
}
