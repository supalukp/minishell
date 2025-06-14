/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:50:16 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/08 17:54:45 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	option_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	else
		i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_tree *tree)
{
	int		i;
	int j;
	bool	noline_flag;
	char	**cmd;

	if (!tree)
		return (0);
	cmd = combine_cmdline(tree->cmd_line);
	noline_flag = false;
	i = 1;
	while (cmd[i] != NULL && option_n(cmd[i]))
	{
		noline_flag = true;
		i++;
	}
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\\' && tree->cmd_line->next->quoted != 2 && tree->cmd_line->next->quoted != 1)
				j++;
			printf("%c", cmd[i][j]);
			j++;
		}
		// printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (noline_flag == false)
		printf("\n");
	free_matrix(cmd);
	return (0);
}
