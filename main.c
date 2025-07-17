/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/07/17 15:45:51 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_data	request;
	char	*prompt;
	char	*temp_line;

	(void)ac;
	(void)av;
	// if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	// 	return (1);
	rl_event_hook = signal_event;
	request.env = env_init(env);
	signal(SIGPIPE, SIG_IGN);
	request.last_exit = 0;
	g_signal = 0;
	while (1)
	{
		init_signal();
		prompt = build_prompt(request.last_exit);
		g_signal = 0;
		if (isatty(fileno(stdin)))
			line = readline(prompt);
		else
		{
			temp_line = get_next_line(fileno(stdin));
			line = ft_strtrim(temp_line, "\n");
			free(temp_line);
		}
		free(prompt);
		if (g_signal == 130)
		{
			request.last_exit = 130;
			continue ;
		}
		if (line == NULL)
		{
			// write(1, "exit\n", 5);
			free_env(request.env);
			rl_clear_history();
			exit(request.last_exit);
		}
		if (*line)
			add_history(line);
		handle_line(line, &request);
	}
	free_env(request.env);
	rl_clear_history();
	return (0);
}
