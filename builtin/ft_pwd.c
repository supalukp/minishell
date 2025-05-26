/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:50:54 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/25 10:56:31 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int ft_pwd(t_tree_token *tree)
{
	char *res;
	
	if (tree && tree->cmd_line && tree->cmd_line->next && tree->cmd_line->next->content)
	{
		if (tree->cmd_line->next->content[0] == '-')
		{
			ft_putstr_fd("pwd: invalid option\n", 2);
			return (2);
		}
	}
	res = getcwd(NULL, 1024);
	if (res == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		return (1);
	}
	if (res)
	{
		printf("%s\n", res);
		free(res);
	}
	return (0);
}
