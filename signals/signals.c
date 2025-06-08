/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 09:25:01 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/08 12:22:37 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

volatile sig_atomic_t trigger = 0;

void handler_signal(int sig)
{
	// (void)sig;
	if (sig == SIGINT)
	{
		trigger = 1;
		printf("\n");
	}
	else if (sig == SIGQUIT)
		printf("hello2\n");
}
