/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:47:57 by syukna            #+#    #+#             */
/*   Updated: 2025/07/22 17:58:37 by syukna           ###   ########.fr       */
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

// clean.c
void	clean_data(t_data *data);
void	clean_recursive_tree(t_tree *node);

// error_checking.c
int		only_space(char *line);
int		only_colon(const char *line);
int		only_exclamation(const char *line);
int		open_quotes(char *line);
int		no_files(char *line);
int		check_semi(char *line);
int		unsupported_syntax(char *line);
int		error_checking(char *line, t_data *data);
int		check_bracket_error(char *line);

// readline_utils.c
char	*build_prompt(int exit_status);

// handle_line.c
void	handle_line(char *line, t_data *request);

// separator.c
void	parse_separator(char *substr, t_tree *parent, int *error);

// parsing.c
t_tree	*mns_parse(char *line);
t_type	has_operator(char *ss, t_type op);
t_tree	*ast_maker(char *substr, int *error);

// parenthesis.c
int		contains_letter(char *substr, char letter);
int		is_letters(char letter, char *substr);
void	remove_parenthesis(char **substr, int *error);

// cmd_line.c
void	command_line_maker(t_tree *cmd_line, int *error, t_data *request);
void	add_cmd_file(char *ctt, t_type type, t_tree *ln, int *error);

// redirections.c
void	identify_redirections(t_tree *cmd_line, int *error);
void	remove_redirection(int index, t_tree *cmd_line, int *error);
t_type	define_redirection_type(int index, char *cmd_line);
void	get_redirections(int index, t_tree *cmd_line, int *error);
char	*get_redirection_file(int index, char *cmd_line, int *error);
void	remove_quotes_redirections(t_tree *cmd_line);

// expansions.c
int		add_expansions(t_tree *node, t_env *lst, t_data *request);
int		current_pos_dollar(char *line, int count);
int		expand_score(t_tree *node, t_env *lst);
void	replace_expansion(t_cmd_element *l, t_env *lst, int *count);
void	add_tild(t_cmd_element *element, t_env *lst);
void	spec_dol(t_cmd_element *line, int *count, int code);
void	trim_space(t_cmd_element *cmd);
int		counterchar(char const *s1, char letter);
char	*find_expansion_match(const char *search, t_env *lst);
void	exchange_expansion_values(t_cmd_element *el, char *new, int i, int len);

// cmd_mergequotes.c
void	merge_cmd_quotes(t_tree *node);

void	split_cmd_elements(t_tree *cmd_line, int *error);
void	remove_cmd_element(t_tree *cmd_line, int quoted, int *error);
int		get_element_len(char *line, int quoted);
void	handle_remcmd(char *rtnstr, t_tree *cmd_line, size_t rmlen, int *error);

#endif