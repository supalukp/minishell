/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:48:43 by syukna            #+#    #+#             */
/*   Updated: 2025/06/06 15:09:27 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "headings.h"
# include <stdbool.h>

typedef enum e_type
{
	CMD_LINE,
	PIPE,
	AND,
	OR,
	APPEND,
	HEREDOC,
	INFILE,
	OUTFILE,
	INVALID
}							t_type;

typedef struct s_cmd_element
{
	char					*content;
	int						quoted;
	struct s_cmd_element	*next;
}							t_cmd_element;

typedef struct s_file
{
	char					*content;
	t_type					type;
	int						quoted;
	struct s_file			*next;
}							t_file;

typedef struct s_tree
{
	char					*content;
	t_type					type;
	t_cmd_element			*cmd_line;
	t_file					*files;
	struct s_tree			*left;
	struct s_tree			*right;
}							t_tree;

typedef struct s_env
{
	char					*env_name;
	char					*env_variable;
	struct s_env			*next;
}							t_env;

typedef struct s_pipe_cmds
{
	t_tree					*cmd;
	struct s_pipe_cmds		*next;
}							t_pipe_cmds;

typedef struct s_pipes
{
	int						pipes_count;
	int						process;
	int						**pipefd;
	pid_t					*pid;
	t_pipe_cmds				*cmd_lst;
}							t_pipes;

typedef struct s_data
{
	t_tree					*ast;
	t_env					*env;
	int						last_exit;
}							t_data;

#endif