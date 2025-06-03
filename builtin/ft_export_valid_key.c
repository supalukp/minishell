/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_valid_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:32:16 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/03 14:39:18 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	not_valid_identifier(void)
{
	ft_putstr_fd("export: not a valid identifier\n", 2);
	return (1);
}

int	not_valid_name(char *args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (args[i] == '=')
	{
		ft_putstr_fd("export: not a valid identifier\n", 2);
		return (1);
	}
	while (args[i] && args[i] != '=' && !(args[i] == '+' && args[i + 1] == '='))
	{
		if (i == 0 && (args[i] != '_' && !ft_isalpha(args[i])))
			return (not_valid_identifier());
		else if (args[i] != '_' && !ft_isalnum(args[i]))
			return (not_valid_identifier());
		else
			i++;
	}
	return (flag);
}

int	export_invalid_option(t_cmd_element *args)
{
	if (args->content[0] == '-')
	{
		ft_putstr_fd("export: invalid option\n", 2);
		return (1);
	}
	return (0);
}
