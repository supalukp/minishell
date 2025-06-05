/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:47:57 by syukna            #+#    #+#             */
/*   Updated: 2025/05/29 15:29:52 by syukna           ###   ########.fr       */
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
void			parse_separator(char *substr, t_tree *parent, int *error);

// parsing.c
t_tree			*mns_parse(char *line);
t_type			is_operator(char *line);
t_tree			*ast_maker(char *substr, int *error);

// visual.c
void			print_files(t_file *file);
void			print_node(t_tree *node, t_env *lst);
void			print_all(t_data *request, t_env *lst);

// parenthesis.c
int				contains_letter(char *substr, char letter);
int				is_letters(char letter, char *substr);
void			remove_parenthesis(char **substr, int *error);

// cmd_line.c
void			command_line_maker(t_tree *cmd_line, int *error);

// redirections.c
void			identify_redirections(t_tree *cmd_line, int *error);
void			remove_redirection(int index, t_tree *cmd_line, int *error);
char			*get_redirection_file(int index, char *cmd_line, int *error);
t_type			define_redirection_type(int index, char *cmd_line);
void			get_redirections(int index, t_tree *cmd_line, int *error);

// cmd_ll_files.c
void			add_cmd_file(char *ctt, t_type type, t_tree *ln, int *error);

// cmd_elements.c
void			split_cmd_elements(t_tree *cmd_line, int *error);

// clean.c
void			clean_data(t_data *data);
void			clean_recursive_tree(t_tree *node);

// cmd_expansions.c
char	*find_expansion_match(const char *search, t_env *lst);
int	add_expansions(t_tree *node, t_env *lst);

/* ************************************************************************** */
/* ***********************************EXEC*********************************** */
/* ************************************************************************** */

// env_init.c
t_env *env_init(char **env);
void print_env(t_env *lst);

#endif