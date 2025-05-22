/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_ft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:49:36 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/22 14:43:24 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	ft_echo(t_tree_token *tree)
{
	int		i;
	bool	noline_flag;
	char	**cmd;

	if (!tree)
		return (0);
	cmd = combine_cmdline(tree->cmd_line);
	noline_flag = false;
	i = 1;
	while (cmd[i] != NULL && strcmp(cmd[i], "-n") == 0)
	{
		noline_flag = true;
		i++;
	}
	
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (noline_flag == false)
		printf("\n");
	free_matrix(cmd);
	return (0);
}

int ft_pwd(t_tree_token *tree)
{
	char *res;
	
	if (tree && tree->cmd_line && tree->cmd_line->next && tree->cmd_line->next->content)
	{
		if (tree->cmd_line->next->content[0] == '-')
		{
			write(2, "pwd : bad option\n", 17);
			return (1);
		}
	}
	res = getcwd(NULL, 1024);
	if (res == NULL)
	{
		printf("Get current working directory failed.\n");
		return (1);
	}
	if (res)
	{
		printf("%s\n", res);
		free(res);
	}
	return (0);
}
