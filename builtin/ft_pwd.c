/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:50:54 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/23 13:44:33 by spunyapr         ###   ########.fr       */
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
