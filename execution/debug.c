/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:03:18 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/05 16:29:01 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	check_if_buildin(t_token *tree)
{
	if (is_buildin(tree->name) == true)
		printf("true\n");
	else
		printf("false\n");
}
