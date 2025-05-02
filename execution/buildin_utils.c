/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:22:31 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/02 15:50:32 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

bool is_buildin(char *args)
{
    char **cmd;

    cmd = ft_split(args, ' ');
    
    printf("cmd[0] = %s\n", cmd[0]);
    if (!ft_strcmp(cmd[0], "echo"))
        return (true); 
    else if (!ft_strcmp(cmd[0], "cd"))
        return (true); 
    else if (!ft_strcmp(cmd[0], "pwd"))
        return (true); 
    else if (!ft_strcmp(cmd[0], "export"))
        return (true); 
    else if (!ft_strcmp(cmd[0], "unset"))
        return (true);
    else if (!ft_strcmp(cmd[0], "env"))
        return (true); 
    else if (!ft_strcmp(cmd[0], "exit"))
        return (true);
    else
        return (false);
}


