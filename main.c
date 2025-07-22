/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/07/22 16:10:56 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

volatile sig_atomic_t	g_signal = 0;

static void	setup_shell(t_data *request, char **env)
{
	rl_event_hook = signal_event;
	signal(SIGPIPE, SIG_IGN);
	request->env = env_init(env);
	request->last_exit = 0;
	g_signal = 0;
}

static void	shell_loop(t_data *request)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		init_signal();
		prompt = build_prompt(request->last_exit);
		g_signal = 0;
		line = readline(prompt);
		free(prompt);
		if (g_signal == 130)
		{
			request->last_exit = 130;
			continue ;
		}
		if (!line)
			break ;
		if (*line)
			add_history(line);
		handle_line(line, request);
	}
}

static void	safe_exit(t_data *request)
{
	write(1, "exit\n", 5);
	free_env(request->env);
	rl_clear_history();
	exit(request->last_exit);
}

int	main(int ac, char **av, char **env)
{
	t_data	request;

	(void)ac;
	(void)av;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (1);
	setup_shell(&request, env);
	shell_loop(&request);
	safe_exit(&request);
	return (0);
}
