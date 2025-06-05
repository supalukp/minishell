/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:48:43 by syukna            #+#    #+#             */
/*   Updated: 2025/06/05 17:00:37 by spunyapr         ###   ########.fr       */
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
	// CMD,
	// ARG,
	APPEND,
	HEREDOC,
	INFILE,
	OUTFILE,
	INVALID
}					t_type;

typedef struct s_cmd_element
{
	char					*content; // "ls"
	int						quoted; // 0quoteless, 1single, 2double
	struct s_cmd_element	*next; // token "ls -a"
}					t_cmd_element;

typedef struct s_file
{
	char *content;              // "ls"
	t_type type;                // CMD
	int quoted;                 // 0 when no quotes, 1 when single 2 when double
	struct s_file *next; // token "ls -a"
}					t_file;

typedef struct s_tree
{
	char *content;           // "ls -a"
	t_type type;             // CMD_LINE
	t_cmd_element *cmd_line; // linked list of all non file expanded elements
	t_file			*files;
	struct s_tree *left;  // token "ls -a"
	struct s_tree *right; // NULL
}					t_tree;

typedef struct s_env
{
	char			*env_name;
	char *env_variable;
	struct s_env *next;
}					t_env;

typedef struct s_pipe_cmds
{
	t_tree			*cmd;
	struct s_pipe_cmds		*next;
}							t_pipe_cmds;

typedef struct s_pipes
{
	int				pipes_count;
	int				process;
	int				**pipefd;
	pid_t			*pid;
	t_pipe_cmds		*cmd_lst;
}					t_pipes;

typedef struct s_data
{
	t_tree	*ast;
	t_env			*env;
	int			last_exit;
}					t_data;

#endif