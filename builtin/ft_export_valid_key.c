/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_valid_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:32:16 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 16:52:00 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	not_valid_identifier(char *function)
{
	ft_putstr_fd(function, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return (1);
}

int	not_valid_name(char *args, char *function)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (args[i] == '=')
		return (not_valid_identifier(function));
	while (args[i] && args[i] != '=' && !(args[i] == '+' && args[i + 1] == '='))
	{
		if (i == 0 && (args[i] != '_' && !ft_isalpha(args[i])))
			return (not_valid_identifier(function));
		else if (args[i] != '_' && !ft_isalnum(args[i]))
			return (not_valid_identifier(function));
		else
			i++;
	}
	return (flag);
}

int	invalid_option(t_cmd_element *args, char *function)
{
	if (args->content[0] == '-')
	{
		ft_putstr_fd(function, 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (1);
	}
	return (0);
}
