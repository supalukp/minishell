/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:48:43 by syukna            #+#    #+#             */
/*   Updated: 2025/05/26 16:52:26 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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
	APPEND,
	HEREDOC,
	INFILE,
	OUTFILE,
	INVALID
}					t_type;

typedef struct s_cmd_element
{
	char *content;              // "ls"
	t_type type;                // CMD
	int quoted;                 // 0 when no quotes, 1 when single 2 when double
	struct s_cmd_element *next; // token "ls -a"
}					t_cmd_element;

typedef struct s_file
{
	char *content;       // "text.txt"
	t_type type;         // HEREDOC? INFILE? OUTFILE?
	struct s_file *next; // next file from same type
}					t_file;

typedef struct s_tree_token
{
	char *content;           // "ls -a"
	t_type type;             // CMD_LINE
	t_cmd_element *cmd_line; // linked list of all non file expanded elements
	t_file			*files;
	int fd_in;
	int fd_out;
	struct s_tree_token *left;  // token "ls -a"
	struct s_tree_token *right; // NULL
}					t_tree_token;

typedef struct s_env
{
	char			*env_name;
	char *env_variable;
	struct s_env *next;
}					t_env;

typedef struct s_pipe_cmds
{
	t_tree_token			*cmd;
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
	t_tree_token	*ast;
	t_env			*env;
	int			last_exit;
}					t_data;

#endif