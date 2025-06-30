/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/06/30 14:17:17 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

volatile sig_atomic_t g_signal = 0;

void close_all_heredoc_fd(t_tree *tree)
{
	if (tree == NULL)
		return ;
    if (tree->type == PIPE || tree->type == OR || tree->type == AND) 
	{
        close_all_heredoc_fd(tree->left);
        close_all_heredoc_fd(tree->right);
    } 
	else if (tree->type == CMD_LINE)
	{
		if (tree->fd_heredoc != -1)
			close(tree->fd_heredoc);
	}
}

int traverse_heredoc(t_tree *tree, t_data *data)
{
	int status;
	t_tree *node;
	t_file *file;
	int error;

	error = 0;
	node = tree;
	if (node == NULL)
		return 0;
    if (node->type == PIPE || node->type == OR || node->type == AND) 
	{
        status = traverse_heredoc(node->left, data);
		if (status != 0)
        	return (status);
        status = traverse_heredoc(node->right, data);
		if (status != 0)
        	return (status);
    } 
	else if (node->type == CMD_LINE)
	{
		command_line_maker(node, &error, data);
		file = node->files;
		while (file)
		{
			if (file->type == HEREDOC)
			{
				status = redirect_heredoc(file, node);
				if (status != 0)
				{
					close_all_heredoc_fd(tree);
					return (status);
				}
			}
			file = file->next;
		}
	}
	return (0);
}

void	handle_line(char *line, t_data *request)
{
	t_tree	*tree;
	int	exit_status;

	exit_status = error_checking(line, request);
	if (exit_status != 0) 
	{
		request->last_exit = exit_status;
		return ;
	}
	if (only_space(line) || only_colon(line) || only_exclamation(line))
		return ;
	tree = mns_parse(line);
	request->ast = tree;
	if (request->ast)
	{
		exit_status = traverse_heredoc(request->ast, request);
		if (exit_status != 0)
		{
			request->last_exit = exit_status;
			clean_data(request);
			return ;
		}
		request->last_exit = main_execution(request->ast, request);
		close_save_fd(request->ast);
		clean_data(request);
	}
}

int signal_event(void)
{
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_data	request;
	char *prompt;
	(void)ac;
	(void)av;
	
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
            char *temp_line = get_next_line(fileno(stdin));
            line = ft_strtrim(temp_line, "\n");
            free(temp_line);
        }
		free(prompt);
		if (g_signal == 130)
		{
			request.last_exit = 130;
			continue;
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
	// if (request.env)
	free_env(request.env);
	// if (line)
    // 	free(line);
	rl_clear_history();
	return (0);
}
