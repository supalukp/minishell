/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:33:38 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/15 15:47:05 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	free_double_array(int **double_array)
{
	int	i;

	i = 0;
	if (!double_array)
		return ;
	while (double_array[i])
	{
		free(double_array[i]);
		double_array[i] = NULL;
		i++;
	}
	free(double_array);
	double_array = NULL;
}