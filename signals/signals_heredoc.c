/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:23:23 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/20 15:08:07 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	handle_heredoc_sigint(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	setup_heredoc_signal(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = handle_heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
