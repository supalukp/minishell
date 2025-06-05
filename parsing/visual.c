/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:30:04 by syukna            #+#    #+#             */
/*   Updated: 2025/05/29 15:29:29 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

char *types_text[] = { "CMD_LINE", "PIPE","AND","OR","CMD","ARG","APPEND","HEREDOC","INFILE","OUTFILE","INVALID"};

void	print_files(t_file *file)
{
	printf("*    File name: |%s|\n", file->content);
	printf("*    File type: %s\n", types_text[file->type] );
}

void 	print_cmd_elements(t_cmd_element *cmd_element)
{
	printf("*    command content: |%s|\n", cmd_element->content);
	printf("*    cmd_element quoted: %d\n", cmd_element->quoted);
}

void	print_node(t_tree *node, t_env *lst)
{
	t_file *temp_file;
	t_cmd_element *temp_cmd_element;

	printf("***************************************************\n");
	printf("* Content: |%s|\n", node->content);
	printf("* Type: %s\n", types_text[node->type]);
	add_expansions(node, lst);
	if (node->left)
	{
		if (node->left->type == CMD_LINE)
			printf("* Left link: %s\n", node->left->content);
		else 
			printf("* Left link: Operator type %s\n", types_text[node->left->type]);
	}
	if (node->right)
	{
		if (node->right->type == CMD_LINE)
			printf("* right link: %s\n", node->right->content);
		else
			printf("* right link: Operator type %s\n",  types_text[node->right->type]);
	}
	if (node->cmd_line)
	{
		printf("*\n* COMMAND ELEMENTS:\n");
		temp_cmd_element = node->cmd_line;
		while(temp_cmd_element->next)
		{
			print_cmd_elements(temp_cmd_element);
			temp_cmd_element = temp_cmd_element->next;
		}
		print_cmd_elements(temp_cmd_element);
	}
	if (node->redirections)
	{
		printf("*\n* FILES:\n");
		temp_file = node->redirections;
		while(temp_file->next)
		{
			print_files(temp_file);
			temp_file = temp_file->next;
		}
		print_files(temp_file);
	}
	printf("***************************************************\n\n");
}

void	print_recursive_tree(t_tree *node, t_env *lst)
{
	print_node(node, lst);
	if(node->left)
		print_recursive_tree(node->left, lst);
	if(node->right)
		print_recursive_tree(node->right, lst);
}

void	print_all(t_data *request, t_env *lst)
{
	printf("********************************************************\n");
	printf("* REQUEST DATASHEET:\n*\n");
	printf("********************************************************\n\n");
	print_recursive_tree(request->ast, lst);
}