/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:52:02 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/06 17:42:19 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "../inc/headings.h"
# include "headings.h"
# include "structures.h"

/* ************************************************************************** */
/* *********************************PARSING********************************** */
/* ************************************************************************** */

// separator.c
void	parse_separator(char *substr, t_tree *parent, int *error);

// parsing.c
t_tree			*mns_parse(char *line);
t_type			has_operator(char *line, t_type	operator);
t_tree			*ast_maker(char *substr, int *error);

// visual.c
void	print_files(t_file *file);
void	print_node(t_tree *node);
void	print_all(t_data *request);

// parenthesis.c
int		contains_letter(char *substr, char letter);
int		is_letters(char letter, char *substr);
void	remove_parenthesis(char **substr, int *error);

// cmd_line.c
void	command_line_maker(t_tree *cmd_line, int *error);

// redirections.c
void	identify_redirections(t_tree *cmd_line, int *error);
void	remove_redirection(int index, t_tree *cmd_line, int *error);
char	*get_redirection_file(int index, char *cmd_line, int *error);
t_type	define_redirection_type(int index, char *cmd_line);
void	get_redirections(int index, t_tree *cmd_line, int *error);

// cmd_ll_files.c
void	add_cmd_file(char *ctt, t_type type, t_tree *ln, int *error);

// cmd_elements.c
void	split_cmd_elements(t_tree *cmd_line, int *error);

// clean.c
void	clean_data(t_data *data);
void	clean_recursive_tree(t_tree *node);

/* ************************************************************************** */
/* ***********************************EXEC*********************************** */
/* ************************************************************************** */

#endif