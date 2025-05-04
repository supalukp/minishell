/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:47:57 by syukna            #+#    #+#             */
/*   Updated: 2025/05/04 14:05:26 by syukna           ###   ########.fr       */
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
void	parse_separator(char *substr, t_token *parent);

// parsing.c
t_token	*mns_parse(char *line);
t_type	is_operator(char *line);
t_token *AST_maker(char *substr);

// visual.c
void	print_node(t_token *node);

// parenthesis.c
int	contains_letter(char *substr, char letter);
void	remove_parenthesis(char **substr);

/* ************************************************************************** */
/* ***********************************EXEC*********************************** */
/* ************************************************************************** */

#endif