/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_separator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:25:49 by syukna            #+#    #+#             */
/*   Updated: 2025/06/19 14:34:31 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

size_t	parse_len_first(char *ss, t_type op)
{
	size_t	i;
	int		par;
	int		pos;

	i = 0;
	pos = 0;
	par = 0;
	while (ss[i])
	{
		if (ss[i] == '(')
			par += 1;
		if (ss[i] == ')')
			par -= 1;
		if (op == PIPE && ss[i] == '|' && par == 0)
			pos = i;
		if (op == AND && ss[i] == '&' && ss[i + 1] == '&' && par == 0)
			pos = i;
		if (op == OR && ss[i] == '|' && ss[i + 1] == '|' && par == 0)
			pos = i;
		i++;
	}
	return (pos);
}

char	*parse_get_first(char *substr, t_type operator, int *error)
{
	size_t		len;
	char		*subfirst;

	len = parse_len_first(substr, operator);
	subfirst = ft_calloc(len + 1, sizeof(char));
	if (!subfirst)
		return (*error = 1, NULL);
	ft_strlcpy(subfirst, substr, len + 1);
	return (subfirst);
}

size_t	parse_pos_second(char *ss, t_type op)
{
	size_t	i;
	int		pos;
	int		par;

	i = 0;
	pos = 0;
	par = 0;
	while (ss[i])
	{
		if (ss[i] == '(')
			par += 1;
		if (ss[i] == ')')
			par -= 1;
		if (op == PIPE && ss[i] == '|' && par == 0)
			pos = i;
		if (op == AND && ss[i] == '&' && ss[i - 1] == '&' && par == 0)
			pos = i;
		if (op == OR && ss[i] == '|' && ss[i - 1] == '|' && par == 0)
			pos = i;
		i++;
	}
	return (pos + 1);
}

char	*parse_get_second(char *substr, t_type operator, int *error)
{
	size_t		pos;
	char		*subsecond;

	pos = parse_pos_second(substr, operator);
	subsecond = NULL;
	subsecond = ft_strtrim(&substr[pos], " ");
	if (!subsecond)
		return (*error = 1, NULL);
	return (subsecond);
}

void	parse_separator(char *substr, t_tree *parent, int *error)
{
	char	*first;
	char	*second;

	first = parse_get_first(substr, parent->type, error);
	parent->left = ast_maker(first, error);
	second = parse_get_second(substr, parent->type, error);
	parent->right = ast_maker(second, error);
}
