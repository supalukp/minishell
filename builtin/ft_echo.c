/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:50:16 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 16:05:44 by spunyapr         ###   ########.fr       */
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

static bool	check_n_option(char **cmd, int *i)
{
	bool	noline_flag;

	noline_flag = false;
	while (cmd[*i] != NULL && option_n(cmd[*i]))
	{
		noline_flag = true;
		(*i)++;
	}
	return (noline_flag);
}

static void	print_echo_argument(char *arg, t_tree *tree)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == '\\' && tree->cmd_line->next->quoted != 2
			&& tree->cmd_line->next->quoted != 1)
			j++;
		if (arg[j] == '\t')
			printf(" ");
		while (arg[j] == '\t')
			j++;
		printf("%c", arg[j]);
		j++;
	}
}

static void	print_echo_args(char **cmd, int i, t_tree *tree)
{
	while (cmd[i])
	{
		print_echo_argument(cmd[i], tree);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
}

int	ft_echo(t_tree *tree)
{
	int		i;
	bool	noline_flag;
	char	**cmd;

	i = 1;
	if (!tree)
		return (0);
	cmd = combine_cmdline(tree->cmd_line);
	noline_flag = check_n_option(cmd, &i);
	print_echo_args(cmd, i, tree);
	if (!noline_flag)
		printf("\n");
	free_matrix(cmd);
	return (0);
}
