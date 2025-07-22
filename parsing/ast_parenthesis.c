/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parenthesis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:13:37 by syukna            #+#    #+#             */
/*   Updated: 2025/07/22 17:21:37 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	contains_letter(char *substr, char letter)
{
	int	i;

	i = 0;
	while (substr[i])
	{
		if (substr[i] == letter)
			return (1);
		i++;
	}
	return (0);
}

int	is_letters(char letter, char *substr)
{
	int	i;

	i = 0;
	while (substr[i])
	{
		if (substr[i] == letter)
			return (1);
		i++;
	}
	return (0);
}

static void	par_letter(char *substr, int *par, char *str_without)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (substr[i])
	{
		if (substr[i] == '(')
		{
			*par += 1;
			if (*par != 1)
				str_without[j++] = substr[i];
		}
		else if (substr[i] == ')')
		{
			*par -= 1;
			if (*par != 0)
				str_without[j++] = substr[i];
		}
		else
			str_without[j++] = substr[i];
		i++;
	}
}

void	remove_parenthesis(char **substr, int *error)
{
	int		len;
	int		par;
	char	*str_without;

	len = ft_strlen(*substr) - 1;
	par = 0;
	str_without = ft_calloc(len, sizeof(char));
	if (!str_without)
	{
		*error = 1;
		return ;
	}
	par_letter(*substr, &par, str_without);
	free(*substr);
	*substr = str_without;
}
