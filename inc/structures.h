/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:48:43 by syukna            #+#    #+#             */
/*   Updated: 2025/05/28 15:47:02 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "headings.h"
# include <stdbool.h>

typedef enum e_type
{
	// AST TREE LEVEL
	CMD_LINE,
	PIPE,
	AND,
	OR,
	// CMD_LINE LEVEL
	CMD,
	ARG,
	INFILE,
	HEREDOC,
	OUTFILE,
	OUTFILE_APPEND,
	INVALID
}			t_type;

typedef struct s_cmd_element
{
	char					*content; // "ls"
	int						quoted; // 0quoteless, 1single, 2double
	struct s_cmd_element	*next; // token "ls -a"
}					t_cmd_element;

typedef struct s_file
{
	char				*content; // "text.txt"
	t_type				type; // HEREDOC? INFILE? OUTFILE?
	struct s_file		*next;
}					t_file;

typedef struct s_tree_token
{
	char				*content; // "ls -a"
	t_type				type; // CMD_LINE
	t_cmd_element		*cmd_line; // all non file expanded el
	t_file				*redirections;
	struct s_tree_token	*left; // token "ls -a"
	struct s_tree_token	*right; // NULL
}					t_tree;

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_tree			*ast;
	t_env			*env;
}					t_data;

#endif