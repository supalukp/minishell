/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:43:39 by syukna            #+#    #+#             */
/*   Updated: 2025/06/09 17:27:41 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int str_is_digit(char *str)
{
	int i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_exit(t_tree *tree, int exit_status)
{ 
	if (tree->cmd_line->next)
	{
		if (tree->cmd_line->next->next)
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			if (!str_is_digit(tree->cmd_line->next->content))
				exit(255);
			else 
				return (2);
		}
		else if (!str_is_digit(tree->cmd_line->next->content))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(tree->cmd_line->next->content, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		else
		{
			write(2, "exit\n", 5);
			exit(ft_atoi(tree->cmd_line->next->content) % 256);
		}
	}
	exit(exit_status);
}
