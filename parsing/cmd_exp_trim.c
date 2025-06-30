/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exp_trim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:50:29 by syukna            #+#    #+#             */
/*   Updated: 2025/06/30 12:53:50 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	skip_and_copy(const char *src, char *dst, int *i, int *j)
{
	int	in_word;

	in_word = 0;
	while (src[*i])
	{
		if (src[*i] == ' ')
		{
			if (in_word)
				dst[(*j)++] = ' ';
			in_word = 0;
		}
		else
		{
			dst[(*j)++] = src[*i];
			in_word = 1;
		}
		(*i)++;
	}
}

void	trim_space(t_cmd_element *cmd)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (!cmd || cmd->quoted == 2 || !cmd->content)
		return ;
	new_str = ft_calloc(ft_strlen(cmd->content) + 1, sizeof(char));
	if (!new_str)
		return ;
	while (cmd->content[i] == ' ')
		i++;
	skip_and_copy(cmd->content, new_str, &i, &j);
	if (j > 0 && new_str[j - 1] == ' ')
		j--;
	new_str[j] = '\0';
	free(cmd->content);
	cmd->content = new_str;
}
