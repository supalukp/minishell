/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_separator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:25:49 by syukna            #+#    #+#             */
/*   Updated: 2025/06/05 16:19:04 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

size_t	parse_len_first(char *substr, t_type operator)
{
	size_t	i;
	int	parenthesis;

	i = 0;
	parenthesis = 0;
	while (substr[i])
	{
		if (substr[i]  == '(')
			parenthesis += 1;
		if (substr[i]  == ')')
			parenthesis -= 1;
		if (operator == PIPE && substr[i] == '|' && parenthesis == 0)
			break;
		if (operator == AND && substr[i] == '&' && substr[i + 1] == '&' && parenthesis == 0)
			break;
		if (operator == OR && substr[i] == '|' && substr[i + 1] == '|' && parenthesis == 0)
			break;
		i++;
	}
	return i;
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

size_t	parse_pos_second(char *substr, t_type operator)
{
	size_t	i;
	int	parenthesis;

	i = 0;
	parenthesis = 0;
	while (substr[i])
	{
		if (substr[i]  == '(')
			parenthesis += 1;
		if (substr[i]  == ')')
			parenthesis -= 1;
		if (operator == PIPE && substr[i] == '|' && parenthesis == 0)
			break;
		if (operator == AND && substr[i] == '&' && substr[i - 1] == '&' && parenthesis == 0)
			break;
		if (operator == OR && substr[i] == '|' && substr[i - 1] == '|' && parenthesis == 0)
			break;
		i++;
	}
	return (i + 1);
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