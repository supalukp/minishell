/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:06 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/06 19:05:31 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

int only_space(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int open_quotes(char *line)
{
	int i;
	int single_flag;
	int double_flag;

	i = 0;
	single_flag = 0;
	double_flag = 0;
	while (line[i])
	{
		printf("%c\n", line[i]);
		if ((line[i] == '\'' || line[i] == '"') && (single_flag == 0 && double_flag == 0))
		{
			if (line[i] == '\'')
				single_flag = 1;
			else if (line[i] == '"')
				double_flag = 1;
		}
		else if (line[i] == '\'' && single_flag == 1 && double_flag == 0)
			single_flag = 0;
		else if (line[i] == '"' && double_flag == 1 && single_flag == 0)
			double_flag = 0;
		printf("sin = %d\n", single_flag);
		printf("dou = %d\n", double_flag);
		i++;
	}
	if (single_flag || double_flag)
		return (1);
	return (0);
}

int error_checking(char *line)
{
	if (only_space(line))
		return (1);
	if (open_quotes(line))
		return (1);
	// if (no_files(line))
	// 	return (1);
	return (0);
}

int main (void)
{
	char line[] = "\"ds'd''dsd\"' ";
	printf("%d\n", error_checking(line));
	return (0);
}