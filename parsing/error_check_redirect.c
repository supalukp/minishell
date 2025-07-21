/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:19:36 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/21 16:20:09 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static void	update_quote_flags(char c, int *s_flag, int *d_flag)
{
	if (c == '\'' && !*d_flag)
		*s_flag = !(*s_flag);
	else if (c == '"' && !*s_flag)
		*d_flag = !(*d_flag);
}

static int	check_redirect(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] == '\0' || line[*i] == '<' || line[*i] == '>'
		|| line[*i] == '|' || line[*i] == '&')
		return (1);
	return (0);
}

int	no_files(char *line)
{
	int	i;
	int	s_flag;
	int	d_flag;

	i = 0;
	s_flag = 0;
	d_flag = 0;
	while (line[i])
	{
		update_quote_flags(line[i], &s_flag, &d_flag);
		if ((line[i] == '<' || line[i] == '>') && !d_flag && !s_flag)
		{
			if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>'
					&& line[i + 1] == '>'))
				i += 2;
			else
				i++;
			if (check_redirect(line, &i))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
