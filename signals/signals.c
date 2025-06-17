/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 09:25:01 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/17 15:12:24 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"


void	handle_sigint(int sig)
{
	(void)sig;
	g_signal = 130;
	// write(STDOUT_FILENO, "\n", 1);
	rl_done = 1;
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
}

void	init_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void set_signal_to_default(void)
{
	signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void set_signal_to_ignore(void)
{
	signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}
