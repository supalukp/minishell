/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:47:57 by syukna            #+#    #+#             */
/*   Updated: 2025/05/23 14:06:45 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "headings.h"
# include "structures.h"

/* ************************************************************************** */
/* *********************************PARSING********************************** */
/* ************************************************************************** */

// separator.c
void	parse_separator(char *substr, t_tree_token *parent);

// parsing.c
t_tree_token	*mns_parse(char *line);
t_type	is_operator(char *line);
t_tree_token *ast_maker(char *substr);

// visual.c
void	print_files(t_file *file);
void	print_node(t_tree_token *node);
void	print_all(t_data *request);

// parenthesis.c
int	contains_letter(char *substr, char letter);
int	is_letters(char letter, char *substr);
void	remove_parenthesis(char **substr);

// cmd_line.c
void	command_line_maker(t_tree_token *cmd_line);

// redirections.c
void	identify_redirections(t_tree_token *cmd_line);
void	remove_redirection(int index, t_tree_token *cmd_line);
char	*get_redirection_file(int index, char *cmd_line);
t_type	define_redirection_type(int index, char *cmd_line);
void	get_redirections(int index, t_tree_token *cmd_line);

// cmd_ll_files.c
void	add_cmd_file(char *content, t_type type, t_tree_token *cmdline);

// cmd_elements.c
void	split_cmd_elements(t_tree_token *cmd_line);

/* ************************************************************************** */
/* ***********************************EXEC*********************************** */
/* ************************************************************************** */

#endif