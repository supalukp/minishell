/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:25:13 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 17:18:04 by syukna           ###   ########.fr       */
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
void							default_signal_heredoc(void);
void							setup_signal_heredoc(void);
int								signal_event(void);

#endif