/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:29:48 by syukna            #+#    #+#             */
/*   Updated: 2025/02/28 18:40:24 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atoi(const char *str)
{
	long int	nbr;
	int			i;
	int			neg;

	nbr = 0;
	i = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			neg = -1;
	}
	while (str[i] != '\0' && (ft_isdigit(str[i])))
	{
		if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr + (str[i] - 48);
		if (str[i + 1] != '\0' && (ft_isdigit(str[i + 1])) == 1)
			nbr = nbr * 10;
		i++;
	}
	return (nbr * neg);
}
