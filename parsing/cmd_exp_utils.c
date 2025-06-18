/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:49:07 by syukna            #+#    #+#             */
/*   Updated: 2025/06/18 17:18:17 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	counterchar(char const *s1, char letter)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s1[i] == letter)
			j++;
		i++;
	}
	return (j);
}

int	current_pos_dollar(char *line, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (j == count)
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

char	*find_expansion_match(const char *search, t_env *lst)
{
	while (lst)
	{
		if (ft_strlen(search) == ft_strlen(lst->env_name))
		{
			if (ft_strncmp(search, lst->env_name, ft_strlen(search)) == 0)
				return (lst->env_variable);
		}
		lst = lst->next;
	}
	return ("");
}
