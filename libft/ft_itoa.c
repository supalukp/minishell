/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:28:34 by syukna            #+#    #+#             */
/*   Updated: 2024/11/25 19:26:15 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static int	getnlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

static char	*reverse(char *str, int strlen)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = strlen - 2;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	return (str);
}

static char	*handlenum(int n, char *str, int sl)
{
	int		i;
	int		ng;

	i = 0;
	ng = 1;
	i = 0;
	if (n < 0)
	{
		n = n * -1;
		ng = -1;
	}
	while ((ng == 1 && i < (sl - 1)) || (ng == -1 && i < (sl - 2)))
	{
		str[i] = (n % 10) + 48;
		n /= 10;
		i++;
	}
	if (ng == -1)
	{
		str[i] = '-';
		i++;
	}
	str[i] = '\0';
	return (reverse(str, sl));
}

char	*ft_itoa(int n)
{
	char	*str;
	int		strlen;

	strlen = getnlen(n) + 1;
	if (n < -2147483647)
	{
		str = malloc(12 * sizeof(char));
		if (!str)
			return (NULL);
		ft_strlcpy(str, "-2147483648", 12);
		return (str);
	}
	str = (char *)malloc(strlen * sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	handlenum(n, str, strlen);
	return (str);
}
