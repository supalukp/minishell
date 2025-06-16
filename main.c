/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:06:42 by syukna            #+#    #+#             */
/*   Updated: 2025/06/17 00:02:33 by spunyapr         ###   ########.fr       */
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


// void traverse_heredoc(t_tree *node)
// {
// 	if (node == NULL)
// 		return ;
//     if (node->type == PIPE || node->type == OR || node->type == AND) 
// 	{
//         traverse_tree(node->left);
//         traverse_tree(node->right);
//     } 
// 	else if (node->type == CMD_LINE)
// 	{
// 		while (node->files)
// 		{
// 			if (node->files->type == HEREDOC)
// 				node->fd_heredoc = get_heredoc();
// 			node->files = node->files->next;
// 		}
// 	}
// }

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
	if (have_pipes(tree))
		free(lexer);
	request->ast = tree;
	if (request->ast)
	{
		// print_all(request);
		// get_heredoc();
		// traverse_tree(request->ast);
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
		if (prompt)
			free(prompt);
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			free_env(request.env);
			rl_clear_history();
			exit(131);
		}
		if (*line)
			add_history(line);
		handle_line(line, &request);
	}
	if (request.env)
		free_env(request.env);
	if (line)
    	free(line);
	rl_clear_history();
	return (0);
}
