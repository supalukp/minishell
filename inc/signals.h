/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:25:13 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/17 15:20:42 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal;
void							handle_sigint(int sig);
void							init_signal(void);
void							set_signal_to_default(void);
void							set_signal_to_ignore(void);
void							handle_heredoc_sigint(int sig);
void							default_signal_heredoc(void);
void							setup_signal_heredoc(void);
int								signal_event(void);

#endif