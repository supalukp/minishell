/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_ft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:49:36 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/05 16:49:17 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	ft_echo(char *args)
{
	int		i;
	bool	noline_flag;
	char	**cmd;

	if (!args)
		return (0);
	cmd = ft_split(args, ' ');
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
	return (free(cmd), 0);
}
