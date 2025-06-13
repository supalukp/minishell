/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 09:25:01 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/13 15:43:51 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

// volatile sig_atomic_t g_signal;

void	handle_sigint(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void handle_sigint_child(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// exit(130);
}

void set_signal_to_default(void)
{
	signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
	// struct sigaction sa_int;
	// // struct sigaction sa_quit;

	// sa_int.sa_handler = handle_sigint_child;
	// sigemptyset(&sa_int.sa_mask);
	// sa_int.sa_flags = 0;
	// sigaction(SIGINT, &sa_int, NULL);

	// sa_quit.sa_handler = SIG_DFL;
	// sigemptyset(&sa_quit.sa_mask);
	// sa_quit.sa_flags = 0;
	// sigaction(SIGQUIT, &sa_quit, NULL);
}

