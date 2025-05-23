/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parenthesis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:13:37 by syukna            #+#    #+#             */
/*   Updated: 2025/05/23 13:41:25 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	contains_letter(char *substr, char letter)
{
	int i;

	i = 0;
	while(substr[i])
	{
		if (substr[i] == letter)
			return (1);
		i++;
	}
	return (0);
}

int	is_letters(char letter, char *substr)
{
	int i;

	i = 0;
	while(substr[i])
	{
		if (substr[i] == letter)
			return (1);
		i++;
	}
	
	return (0);
}

void	remove_parenthesis(char **substr)
{
	int		len;
	int		i;
	int		j;
	int		parenthesis;
	char	*str_without;

	len = ft_strlen(*substr) - 1;
	printf("the paren less is len + %d\n", len);
	str_without = ft_calloc(len, sizeof(char));
	if (!str_without)
		exit(0); // TODO handle full exit
	i = 0;
	j = 0;
	parenthesis = 0;
	while((*substr)[i])
	{
		if ((*substr)[i] == '(')
		{
			parenthesis += 1;
			if (parenthesis != 1)
				str_without[j++] = (*substr)[i];
		}
		else if ((*substr)[i] == ')')
		{
			parenthesis -= 1;
			if (parenthesis != 0)
				str_without[j++] = (*substr)[i];
		}
		else
			str_without[j++] = (*substr)[i];
		i++;
	}
	free(*substr);
	*substr = str_without;
}
