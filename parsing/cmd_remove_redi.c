/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_remove_redi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:05:29 by syukna            #+#    #+#             */
/*   Updated: 2025/07/22 16:11:45 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	get_new_redirectionless_str(int index, t_tree *cmd_line)
{
	int	i;

	i = 0;
	while (is_letters(cmd_line->content[index + i], "< >"))
		i++;
	while (cmd_line->content[index + i] != '\0' && cmd_line->content[index
		+ i] != ' ')
		i++;
	return (i);
}

void	get_replacement_len(t_tree *cmd_line, int lenrem, char *replacement)
{
	int	content_len;

	content_len = ft_strlen(cmd_line->content);
	replacement = ft_calloc(content_len - lenrem + 1, sizeof(char));
}

void	remove_redirection(int index, t_tree *cmd_line, int *error)
{
	int		lenrem;
	char	*replacement;
	int		i;

	lenrem = get_new_redirectionless_str(index, cmd_line);
	get_replacement_len(cmd_line, lenrem, replacement);
	if (!replacement)
	{
		free(cmd_line->content);
		*error = 1;
		return ;
	}
	i = 0;
	while (i < index)
	{
		replacement[i] = cmd_line->content[i];
		i++;
	}
	while (cmd_line->content[i + lenrem])
	{
		replacement[i] = cmd_line->content[i + lenrem];
		i++;
	}
	free(cmd_line->content);
	cmd_line->content = replacement;
}
