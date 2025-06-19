/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:30:04 by syukna            #+#    #+#             */
/*   Updated: 2025/06/19 15:15:09 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

char *types_text[] = { "CMD_LINE", "PIPE","AND","OR","APPEND","HEREDOC","INFILE","OUTFILE","INVALID"};

void	print_files(t_file *file)
{
	printf("*    File name: |%s|\n", file->content);
	printf("*    File type: %s\n", types_text[file->type] );
	printf("*    File quoted: %d\n", file->quoted );
}

void 	print_cmd_elements(t_cmd_element *cmd_element)
{
	if (cmd_element->content == NULL)
		printf("*    command content: NULL/\n");
	else
		printf("*    command content: |%s|\n", cmd_element->content);
	if (cmd_element->space_after == 0)
		printf("*    cmd_element spaced: 0/\n");
	else
		printf("*    cmd_element spaced: %d\n", cmd_element->space_after);
	if (cmd_element->quoted == 0)
		printf("*    cmd_element quoted: 0/\n");
	else
		printf("*    cmd_element quoted: %d\n", cmd_element->quoted);
}

void	print_node(t_tree *node)
{
	t_file *temp_file;
	t_cmd_element *temp_cmd_element;

	printf("***************************************************\n");
	printf("* Content: |%s|\n", node->content);
	printf("* Type: %s\n", types_text[node->type]);
	if (node->left)
		printf("* Left link: %s\n", types_text[node->left->type]);
	if (node->right)
		printf("* right link: %s\n",  types_text[node->right->type]);
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
	if (node->files)
	{
		printf("*\n* FILES:\n");
		temp_file = node->files;
		while(temp_file->next)
		{
			print_files(temp_file);
			temp_file = temp_file->next;
		}
		print_files(temp_file);
	}
	printf("***************************************************\n\n");
}

void	print_recursive_tree(t_tree *node)
{
	print_node(node);
	if(node->left)
		print_recursive_tree(node->left);
	if(node->right)
		print_recursive_tree(node->right);
}

void	print_all(t_data *request)
{
	printf("********************************************************\n");
	printf("* REQUEST DATASHEET:\n*\n");
	printf("********************************************************\n\n");
	print_recursive_tree(request->ast);
}