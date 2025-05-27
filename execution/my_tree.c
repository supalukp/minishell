/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:26:23 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/27 17:25:07 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	print_ast(t_tree_token *node)
{
	char **res;
	t_file *file;
	int i;

	i = 0;
	if (!node)
		return ;
	if (node->type == PIPE)
		printf("PIPE: %s\n", node->content);
	else if (node->type == CMD_LINE)
	{
		res = combine_cmdline(node->cmd_line);
		while (res[i])
		{
			printf("%s ", res[i]);
			if (!res[i + 1])
			printf("\n");
			i++;
		}
		free_matrix(res);
		file = node->files;
		while (file)
		{
			printf("file = %s\n", file->content);
			file = file->next;
		}
	}
	print_ast(node->left);
	print_ast(node->right);
}

void	free_file_list(t_file *file)
{
	t_file *tmp;

	while (file)
	{
		tmp = file->next;
		if (file->content)
			free(file->content);
		free(file);
		file = tmp;
	}
}

void	free_ast(t_tree_token *node)
{
	t_cmd_element *tmp_cmd;
	t_cmd_element *next;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->content)
		free(node->content);
	tmp_cmd = node->cmd_line;
	while (tmp_cmd)
	{
		next = tmp_cmd->next;
		if (tmp_cmd->content)
			free(tmp_cmd->content);
		free(tmp_cmd);
		tmp_cmd = next;
	}
	if (node->files)
		free_file_list(node->files);
	free(node);
}


void init_s_main(t_data **data, t_tree_token *tree, char **env)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return;
	(*data)->ast = tree;
	(*data)->env = env_init(env);
	(*data)->last_exit = 0;
}


void try_one_cmd(t_tree_token **tree)
{
	(*tree) = malloc(sizeof(t_tree_token));
	(*tree)->type = CMD_LINE;
	(*tree)->content = ft_strdup("cat -e");
	(*tree)->fd_in = STDIN_FILENO;
	(*tree)->fd_out = STDOUT_FILENO;
	(*tree)->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->cmd_line->content = ft_strdup("echo");
	(*tree)->cmd_line->quoted = 0;
	(*tree)->cmd_line->type = CMD;
	(*tree)->cmd_line->next = malloc(sizeof(t_cmd_element));
	(*tree)->cmd_line->next->content = ft_strdup("-n");
	(*tree)->cmd_line->next->type = ARG;
	(*tree)->cmd_line->next->next = NULL;
	(*tree)->files = malloc(sizeof(t_file));
	(*tree)->files->content = ft_strdup("eof1");
	(*tree)->files->type = HEREDOC;
	(*tree)->files->next = malloc(sizeof(t_file));
	(*tree)->files->next->content = ft_strdup("eof2");
	(*tree)->files->next->type = HEREDOC;
	(*tree)->files->next->next = malloc(sizeof(t_file));
	(*tree)->files->next->next->content = ft_strdup("ouput");
	(*tree)->files->next->next->type = OUTFILE;
	(*tree)->files->next->next->next = NULL; //malloc(sizeof(t_file));
	// (*tree)->files->next->next->next->content = ft_strdup("eof3");
	// (*tree)->files->next->next->next->type = HEREDOC;
	// (*tree)->files->next->next->next->next = NULL;
	(*tree)->left = NULL;
	(*tree)->right = NULL;
}

void one_cmd(t_tree_token **tree)
{
	(*tree) = malloc(sizeof(t_tree_token));
	(*tree)->type = CMD_LINE;
	(*tree)->content = ft_strdup("echo");
	(*tree)->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->cmd_line->content = ft_strdup("echo");
	(*tree)->cmd_line->quoted = 0;
	(*tree)->cmd_line->type = CMD;
	(*tree)->cmd_line->next = NULL; //malloc(sizeof(t_cmd_element));
	// (*tree)->cmd_line->next->content = ft_strdup("-l");
	// (*tree)->cmd_line->next->type = ARG;
	// (*tree)->cmd_line->next->next = NULL; //malloc(sizeof(t_cmd_element));
	// (*tree)->cmd_line->next->next->content = ft_strdup("-nm");
	// (*tree)->cmd_line->next->next->type = ARG;
	// (*tree)->cmd_line->next->next->next = malloc(sizeof(t_cmd_element));
	// (*tree)->cmd_line->next->next->next->content = ft_strdup("hello");
	// (*tree)->cmd_line->next->next->next->next = NULL;
	(*tree)->files = NULL; //malloc(sizeof(t_file));
	// (*tree)->files->content = ft_strdup("outfile4");
	// (*tree)->files->type = OUTFILE;
	// (*tree)->files->next = NULL;
	(*tree)->left = NULL;
	(*tree)->right = NULL;
}

void	pipe_simple_input(t_tree_token **tree)
{
	(*tree) = malloc(sizeof(t_tree_token));
	(*tree)->type = PIPE;
	(*tree)->content = ft_strdup("|");
	(*tree)->cmd_line = NULL;
	(*tree)->files = NULL;
	
	(*tree)->left = malloc(sizeof(t_tree_token));
	(*tree)->left->type = CMD_LINE;
	(*tree)->left->content = ft_strdup("cat -e");
	(*tree)->left->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->left->cmd_line->content = ft_strdup("cat");
	(*tree)->left->cmd_line->quoted = 0;
	(*tree)->left->cmd_line->type = CMD;
	(*tree)->left->cmd_line->next = malloc(sizeof(t_cmd_element));
	(*tree)->left->cmd_line->next->content = ft_strdup("-e");
	(*tree)->left->cmd_line->next->type = ARG;
	(*tree)->left->cmd_line->next->next = NULL;
	(*tree)->left->left = NULL;
	(*tree)->left->right = NULL;
	(*tree)->left->files = malloc(sizeof(t_file));
	(*tree)->left->files->content = ft_strdup("main444.c");
	(*tree)->left->files->type = INFILE;
	(*tree)->left->files->next = malloc(sizeof(t_file));
	(*tree)->left->files->next->content = ft_strdup("eof");
	(*tree)->left->files->next->type = HEREDOC;
	(*tree)->left->files->next->next = NULL;

	(*tree)->right = malloc(sizeof(t_tree_token));
	(*tree)->right->type = CMD_LINE;
	(*tree)->right->content = ft_strdup("grep");
	(*tree)->right->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->right->cmd_line->content = ft_strdup("grep");
	(*tree)->right->cmd_line->quoted = 0;
	(*tree)->right->cmd_line->type = CMD;
	(*tree)->right->cmd_line->next = NULL;
	(*tree)->right->left = NULL;
	(*tree)->right->right = NULL;
	(*tree)->right->files = malloc(sizeof(t_file));
	(*tree)->right->files->content = ft_strdup("outfile0");
	(*tree)->right->files->type = OUTFILE;
	(*tree)->right->files->next = malloc(sizeof(t_file));
	(*tree)->right->files->next->content = ft_strdup("outfile2");
	(*tree)->right->files->next->type = OUTFILE;
	(*tree)->right->files->next->next = NULL;
}

void	complex_pipe_input(t_tree_token **tree)
{
	// cat < Makefile << eof | rev > outfile6 | ls -al > outfile1
	(*tree) = malloc(sizeof(t_tree_token));
	(*tree)->type = PIPE;
	(*tree)->content = ft_strdup("|");
	(*tree)->cmd_line = NULL;
	(*tree)->files = NULL;

	(*tree)->left = malloc(sizeof(t_tree_token));
	(*tree)->left->type = PIPE;
	(*tree)->left->content = ft_strdup("|");
	(*tree)->left->cmd_line = NULL;
	(*tree)->left->files = NULL;

	(*tree)->left->left = malloc(sizeof(t_tree_token));
	(*tree)->left->left->type = CMD_LINE;
	(*tree)->left->left->content = ft_strdup("cat");
	(*tree)->left->left->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->left->left->cmd_line->content = ft_strdup("cat");
	(*tree)->left->left->cmd_line->quoted = 0;
	(*tree)->left->left->cmd_line->type = CMD;
	(*tree)->left->left->cmd_line->next = NULL;
	(*tree)->left->left->left = NULL;
	(*tree)->left->left->right = NULL;

	(*tree)->left->left->files = malloc(sizeof(t_file));
	(*tree)->left->left->files->content = ft_strdup("Makefile");
	(*tree)->left->left->files->type = INFILE;
	(*tree)->left->left->files->next = malloc(sizeof(t_file));
	(*tree)->left->left->files->next->content = ft_strdup("eof1");
	(*tree)->left->left->files->next->type = HEREDOC;
	(*tree)->left->left->files->next->next = NULL;

	(*tree)->left->right = malloc(sizeof(t_tree_token));
	(*tree)->left->right->type = CMD_LINE;
	(*tree)->left->right->content = ft_strdup("rev");
	(*tree)->left->right->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->left->right->cmd_line->content = ft_strdup("rev");
	(*tree)->left->right->cmd_line->quoted = 0;
	(*tree)->left->right->cmd_line->type = CMD;
	(*tree)->left->right->cmd_line->next = NULL;
	(*tree)->left->right->left = NULL;
	(*tree)->left->right->right = NULL;

	(*tree)->left->right->files = malloc(sizeof(t_file));
	(*tree)->left->right->files->content = ft_strdup("outfile6");
	(*tree)->left->right->files->type = OUTFILE;
	(*tree)->left->right->files->next = NULL;

	(*tree)->right = malloc(sizeof(t_tree_token));
	(*tree)->right->type = CMD_LINE;
	(*tree)->right->content = ft_strdup("ls -a");
	(*tree)->right->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->right->cmd_line->content = ft_strdup("ls");
	(*tree)->right->cmd_line->quoted = 0;
	(*tree)->right->cmd_line->type = CMD;

	(*tree)->right->cmd_line->next = malloc(sizeof(t_cmd_element));
	(*tree)->right->cmd_line->next->content = ft_strdup("-a");
	(*tree)->right->cmd_line->next->quoted = 0;
	(*tree)->right->cmd_line->next->type = ARG;
	(*tree)->right->cmd_line->next->next = NULL;

	(*tree)->right->left = NULL;
	(*tree)->right->right = NULL;

	(*tree)->right->files = malloc(sizeof(t_file));
	(*tree)->right->files->content = ft_strdup("outfile1");
	(*tree)->right->files->type = OUTFILE;
	(*tree)->right->files->next = NULL;
}


// void	double_pipes_input(t_tree_token **tree)
// {
//     *tree = malloc(sizeof(t_tree_token));
//     (*tree)->type = PIPE;
//     (*tree)->content = ft_strdup("|");
//     (*tree)->cmd_line = NULL;
//     (*tree)->infiles = NULL;
//     (*tree)->outfiles = NULL;

//     // Left side: echo "hello" | rev
//     (*tree)->left = malloc(sizeof(t_tree_token));
//     (*tree)->left->type = PIPE;
//     (*tree)->left->content = ft_strdup("|");
//     (*tree)->left->cmd_line = NULL;
//     (*tree)->left->infiles = NULL;
//     (*tree)->left->outfiles = NULL;

//     // Left of left: echo "hello"
//     (*tree)->left->left = malloc(sizeof(t_tree_token));
//     (*tree)->left->left->type = CMD_LINE;
//     (*tree)->left->left->content = ft_strdup("echo hello");
//     (*tree)->left->left->cmd_line = malloc(sizeof(t_cmd_element));
//     (*tree)->left->left->cmd_line->content = ft_strdup("echo");
//     (*tree)->left->left->cmd_line->quoted = 0;
//     (*tree)->left->left->cmd_line->type = CMD;

//     (*tree)->left->left->cmd_line->next = malloc(sizeof(t_cmd_element));
//     (*tree)->left->left->cmd_line->next->content = ft_strdup("\"hello\"");
//     (*tree)->left->left->cmd_line->next->quoted = 1;
//     (*tree)->left->left->cmd_line->next->type = ARG;
//     (*tree)->left->left->cmd_line->next->next = NULL;

//     (*tree)->left->left->left = NULL;
//     (*tree)->left->left->right = NULL;
//     (*tree)->left->left->infiles = NULL;
//     (*tree)->left->left->outfiles = NULL;

//     // Right of left: rev
//     (*tree)->left->right = malloc(sizeof(t_tree_token));
//     (*tree)->left->right->type = CMD_LINE;
//     (*tree)->left->right->content = ft_strdup("rev");
//     (*tree)->left->right->cmd_line = malloc(sizeof(t_cmd_element));
//     (*tree)->left->right->cmd_line->content = ft_strdup("rev");
//     (*tree)->left->right->cmd_line->quoted = 0;
//     (*tree)->left->right->cmd_line->type = CMD;
//     (*tree)->left->right->cmd_line->next = NULL;
//     (*tree)->left->right->left = NULL;
//     (*tree)->left->right->right = NULL;
//     (*tree)->left->right->infiles = NULL;
//     (*tree)->left->right->outfiles = NULL;

//     // Right: cat -e
//     (*tree)->right = malloc(sizeof(t_tree_token));
//     (*tree)->right->type = CMD_LINE;
//     (*tree)->right->content = ft_strdup("cat -e");
//     (*tree)->right->cmd_line = malloc(sizeof(t_cmd_element));
//     (*tree)->right->cmd_line->content = ft_strdup("ls");
//     (*tree)->right->cmd_line->quoted = 0;
//     (*tree)->right->cmd_line->type = CMD;

//     (*tree)->right->cmd_line->next = malloc(sizeof(t_cmd_element));
//     (*tree)->right->cmd_line->next->content = ft_strdup("-a");
//     (*tree)->right->cmd_line->next->quoted = 0;
//     (*tree)->right->cmd_line->next->type = ARG;
//     (*tree)->right->cmd_line->next->next = NULL;

//     (*tree)->right->left = NULL;
//     (*tree)->right->right = NULL;
//     (*tree)->right->infiles = NULL;
//     (*tree)->right->outfiles = NULL;
// }

// void	triple_pipes_input(t_tree_token **tree)
// {
// 	// First pipe node: final 'rev'
// 	(*tree) = malloc(sizeof(t_tree_token));
// 	(*tree)->type = PIPE;
// 	(*tree)->content = ft_strdup("|");
// 	(*tree)->cmd_line = NULL;
// 	(*tree)->infiles = NULL;
// 	(*tree)->outfiles = NULL;

// 	// Left: second pipe node (cat -e | rev)
// 	(*tree)->left = malloc(sizeof(t_tree_token));
// 	(*tree)->left->type = PIPE;
// 	(*tree)->left->content = ft_strdup("|");
// 	(*tree)->left->cmd_line = NULL;
// 	(*tree)->left->infiles = NULL;
// 	(*tree)->left->outfiles = NULL;

// 	// Right: rev
// 	(*tree)->right = malloc(sizeof(t_tree_token));
// 	(*tree)->right->type = CMD_LINE;
// 	(*tree)->right->content = ft_strdup("rev");
// 	(*tree)->right->cmd_line = malloc(sizeof(t_cmd_element));
// 	(*tree)->right->cmd_line->content = ft_strdup("rev");
// 	(*tree)->right->cmd_line->type = CMD;
// 	(*tree)->right->cmd_line->next = NULL;
// 	(*tree)->right->left = NULL;
// 	(*tree)->right->right = NULL;
// 	(*tree)->right->infiles = NULL;
// 	(*tree)->right->outfiles = NULL;

// 	// Left-Left: first pipe node (echo "hello" | rev)
// 	t_tree_token *echo_rev_pipe = (*tree)->left;

// 	echo_rev_pipe->left = malloc(sizeof(t_tree_token));
// 	echo_rev_pipe->left->type = PIPE;
// 	echo_rev_pipe->left->content = ft_strdup("|");
// 	echo_rev_pipe->left->cmd_line = NULL;
// 	echo_rev_pipe->left->infiles = NULL;
// 	echo_rev_pipe->left->outfiles = NULL;

// 	// echo "hello"
// 	echo_rev_pipe->left->left = malloc(sizeof(t_tree_token));
// 	echo_rev_pipe->left->left->type = CMD_LINE;
// 	echo_rev_pipe->left->left->content = ft_strdup("echo hello");
// 	echo_rev_pipe->left->left->cmd_line = malloc(sizeof(t_cmd_element));
// 	echo_rev_pipe->left->left->cmd_line->content = ft_strdup("echo");
// 	echo_rev_pipe->left->left->cmd_line->type = CMD;
// 	echo_rev_pipe->left->left->cmd_line->next = malloc(sizeof(t_cmd_element));
// 	echo_rev_pipe->left->left->cmd_line->next->content = ft_strdup("\"hello\"");
// 	echo_rev_pipe->left->left->cmd_line->next->type = ARG;
// 	echo_rev_pipe->left->left->cmd_line->next->next = NULL;
// 	echo_rev_pipe->left->left->left = NULL;
// 	echo_rev_pipe->left->left->right = NULL;
// 	echo_rev_pipe->left->left->infiles = NULL;
// 	echo_rev_pipe->left->left->outfiles = NULL;

// 	// rev (1st)
// 	echo_rev_pipe->left->right = malloc(sizeof(t_tree_token));
// 	echo_rev_pipe->left->right->type = CMD_LINE;
// 	echo_rev_pipe->left->right->content = ft_strdup("rev");
// 	echo_rev_pipe->left->right->cmd_line = malloc(sizeof(t_cmd_element));
// 	echo_rev_pipe->left->right->cmd_line->content = ft_strdup("rev");
// 	echo_rev_pipe->left->right->cmd_line->type = CMD;
// 	echo_rev_pipe->left->right->cmd_line->next = NULL;
// 	echo_rev_pipe->left->right->left = NULL;
// 	echo_rev_pipe->left->right->right = NULL;
// 	echo_rev_pipe->left->right->infiles = NULL;
// 	echo_rev_pipe->left->right->outfiles = NULL;

// 	// cat -e
// 	echo_rev_pipe->right = malloc(sizeof(t_tree_token));
// 	echo_rev_pipe->right->type = CMD_LINE;
// 	echo_rev_pipe->right->content = ft_strdup("cat");
// 	echo_rev_pipe->right->cmd_line = malloc(sizeof(t_cmd_element));
// 	echo_rev_pipe->right->cmd_line->content = ft_strdup("cat");
// 	echo_rev_pipe->right->cmd_line->type = CMD;
// 	echo_rev_pipe->right->cmd_line->next = malloc(sizeof(t_cmd_element));
// 	echo_rev_pipe->right->cmd_line->next->content = ft_strdup("-e");
// 	echo_rev_pipe->right->cmd_line->next->type = ARG;
// 	echo_rev_pipe->right->cmd_line->next->next = NULL;
// 	echo_rev_pipe->right->left = NULL;
// 	echo_rev_pipe->right->right = NULL;
// 	echo_rev_pipe->right->infiles = NULL;
// 	echo_rev_pipe->right->outfiles = NULL;
// }

void	quadruple_pipes_input(t_tree_token **tree)
{
	*tree = malloc(sizeof(t_tree_token));
	(*tree)->type = PIPE;
	(*tree)->content = ft_strdup("|");
	(*tree)->cmd_line = NULL;
	(*tree)->files = NULL;

	// Right: cat -e
	(*tree)->right = malloc(sizeof(t_tree_token));
	(*tree)->right->type = CMD_LINE;
	(*tree)->right->content = ft_strdup("cat -e");
	(*tree)->right->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->right->cmd_line->content = ft_strdup("cat");
	(*tree)->right->cmd_line->type = CMD;

	(*tree)->right->cmd_line->next = malloc(sizeof(t_cmd_element));
	(*tree)->right->cmd_line->next->content = ft_strdup("-e");
	(*tree)->right->cmd_line->next->type = ARG;
	(*tree)->right->cmd_line->next->next = NULL;

	(*tree)->right->left = NULL;
	(*tree)->right->right = NULL;
	(*tree)->right->files = NULL;

	// Left: rev
	(*tree)->left = malloc(sizeof(t_tree_token));
	(*tree)->left->type = PIPE;
	(*tree)->left->content = ft_strdup("|");
	(*tree)->left->cmd_line = NULL;
	(*tree)->left->files = NULL;

	(*tree)->left->right = malloc(sizeof(t_tree_token));
	(*tree)->left->right->type = CMD_LINE;
	(*tree)->left->right->content = ft_strdup("rev");
	(*tree)->left->right->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->left->right->cmd_line->content = ft_strdup("rev");
	(*tree)->left->right->cmd_line->type = CMD;
	(*tree)->left->right->cmd_line->next = NULL;
	(*tree)->left->right->left = NULL;
	(*tree)->left->right->right = NULL;
	(*tree)->left->right->files = NULL;

	// Left-Left: cat -e
	(*tree)->left->left = malloc(sizeof(t_tree_token));
	(*tree)->left->left->type = PIPE;
	(*tree)->left->left->content = ft_strdup("|");
	(*tree)->left->left->cmd_line = NULL;
	(*tree)->left->left->files = NULL;

	(*tree)->left->left->right = malloc(sizeof(t_tree_token));
	(*tree)->left->left->right->type = CMD_LINE;
	(*tree)->left->left->right->content = ft_strdup("cat -e");
	(*tree)->left->left->right->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->left->left->right->cmd_line->content = ft_strdup("cat");
	(*tree)->left->left->right->cmd_line->type = CMD;

	(*tree)->left->left->right->cmd_line->next = malloc(sizeof(t_cmd_element));
	(*tree)->left->left->right->cmd_line->next->content = ft_strdup("-e");
	(*tree)->left->left->right->cmd_line->next->type = ARG;
	(*tree)->left->left->right->cmd_line->next->next = NULL;

	(*tree)->left->left->right->left = NULL;
	(*tree)->left->left->right->right = NULL;
	(*tree)->left->left->right->files = NULL;

	// Left-Left-Left: rev
	(*tree)->left->left->left = malloc(sizeof(t_tree_token));
	(*tree)->left->left->left->type = PIPE;
	(*tree)->left->left->left->content = ft_strdup("|");
	(*tree)->left->left->left->cmd_line = NULL;
	(*tree)->left->left->left->files = NULL;

	(*tree)->left->left->left->right = malloc(sizeof(t_tree_token));
	(*tree)->left->left->left->right->type = CMD_LINE;
	(*tree)->left->left->left->right->content = ft_strdup("rev");
	(*tree)->left->left->left->right->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->left->left->left->right->cmd_line->content = ft_strdup("rev");
	(*tree)->left->left->left->right->cmd_line->type = CMD;
	(*tree)->left->left->left->right->cmd_line->next = NULL;
	(*tree)->left->left->left->right->left = NULL;
	(*tree)->left->left->left->right->right = NULL;
	(*tree)->left->left->left->right->files = NULL;

	// Left-Left-Left-Left: ls
	(*tree)->left->left->left->left = malloc(sizeof(t_tree_token));
	(*tree)->left->left->left->left->type = CMD_LINE;
	(*tree)->left->left->left->left->content = ft_strdup("pwd");
	(*tree)->left->left->left->left->cmd_line = malloc(sizeof(t_cmd_element));
	(*tree)->left->left->left->left->cmd_line->content = ft_strdup("pwd");
	(*tree)->left->left->left->left->cmd_line->type = CMD;
	(*tree)->left->left->left->left->cmd_line->next = NULL;
	(*tree)->left->left->left->left->left = NULL;
	(*tree)->left->left->left->left->right = NULL;
	(*tree)->left->left->left->left->files = NULL;
}


