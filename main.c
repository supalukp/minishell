/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/06/18 00:33:30 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/headings.h"

volatile sig_atomic_t g_signal = 0;


// int get_heredoc(t_tree *tree)
// {
// 	// Case 1 : only one commmand
// 	if (tree->type == CMD_LINE && tree->left == NULL && tree->right == NULL)
// 	{
// 		while (tree->files)
// 		{
// 			if (tree->files->type == HEREDOC)
// 				tree->fd_heredoc = call_heredoc();
// 			tree->files = tree->files->next;
// 		}
// 	}
// 	else if (tree->type == PIPE)
// 	{
// 		while (tree->type == PIPE)
// 		{
			
// 		}
// 	}
// }

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

int traverse_heredoc(t_tree *tree)
{
	int status;
	t_tree *node;
	t_file *file;

	node = tree;
	if (node == NULL)
		return 0;
    if (node->type == PIPE || node->type == OR || node->type == AND) 
	{
        status = traverse_heredoc(node->left);
		if (status != 0)
        	return (status);
        status = traverse_heredoc(node->right);
		if (status != 0)
        	return (status);
    } 
	else if (node->type == CMD_LINE)
	{
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

// void traverse_tree(t_tree *node)
// {
// 	if (node == NULL)
// 		return ;
//     if (node->type == PIPE || node->type == OR || node->type == AND) 
// 	{
//         traverse_tree(node->left);
//         traverse_tree(node->right);
//     } 
// 	else if (node->type == CMD_LINE) 
//         printf("%s\n", node->cmd_line->content);
// }


void	handle_line(char *line, t_data *request)
{
	t_tree	*tree;
	int	exit_status;
	char *lexer;

	exit_status = error_checking(line, request);
	if (exit_status != 0) 
	{
		request->last_exit = exit_status;
		return;
	}
	if (only_space(line) || only_colon(line) || only_exclamation(line))
		return ;
	lexer = merge_quotes(line);
	free(line);
	tree = mns_parse(lexer);
	// if (have_pipes(tree))
	// 	free(lexer);
	request->ast = tree;
	if (request->ast)
	{
		// print_all(request);
		// get_heredoc();
		// traverse_tree(request->ast);
		exit_status = traverse_heredoc(request->ast);
		if (exit_status != 0)
		{
			request->last_exit = exit_status;
			clean_data(request);
			return ;
		}
		request->last_exit = main_execution(request->ast, request);
		// printf("exit status = %d\n", request->last_exit);
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
	request.last_exit = 0;
	g_signal = 0;
	while (1)
	{
		init_signal();
		prompt = build_prompt(request.last_exit);
		g_signal = 0;
		line = readline(prompt);
		free(prompt);
		if (g_signal == 130)
		{
			request.last_exit = 130;
			continue;
		}
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			free_env(request.env);
			rl_clear_history();
			exit(131);
		}
		if (*line)
			add_history(line);
		printf("here\n");
		handle_line(line, &request);
	}
	// if (request.env)
	free_env(request.env);
	// if (line)
    // 	free(line);
	rl_clear_history();
	return (0);
}
