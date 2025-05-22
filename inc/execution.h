/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:31:56 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/22 15:34:14 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "headings.h"


/* -------------------------------------------------------------------------- */
/*                           init_input (hard code)                           */
/* -------------------------------------------------------------------------- */
void		one_cmd(t_tree_token **tree);
void		pipe_simple_input(t_tree_token **tree);
void		print_ast(t_tree_token *node);
void		init_s_main(t_data **data, t_tree_token *tree);
void		double_pipes_input(t_tree_token **tree);
void		triple_pipes_input(t_tree_token **tree);
void		quadruple_pipes_input(t_tree_token **tree);
void	complex_pipe_input(t_tree_token **tree);
/* -------------------------------------------------------------------------- */
/*                                  execution                                 */
/* -------------------------------------------------------------------------- */
char		*find_executable(char **all_path, char *command);
char		*get_path(char *command, char **envp);
void		free_matrix(char **matrix);
char		**combine_cmdline(t_cmd_element *args);
int			main_execution(t_tree_token *tree, char **env, t_data *data);
int			external_single(t_tree_token *tree, char **env);
int			external_cmd_process(t_tree_token *tree, char **env);
int			pipe_process(t_tree_token *tree, char **env, t_data *data);

/* -------------------------------------------------------------------------- */
/*                                    pipes                                   */
/* -------------------------------------------------------------------------- */

void		close_unused_pipes(int i, t_pipes *pipes);
void		setup_inout_first(t_pipes *pipes);
void		setup_inout_last(t_pipes *pipes);
void		setup_inout(int i, t_pipes *pipes);
t_pipe_cmds	*create_pipe_cmd_node(t_tree_token *token);
void		ft_lstadd_cmd_front(t_pipe_cmds **lst, t_pipe_cmds *new);
t_pipe_cmds	*create_cmd_lst(t_tree_token *tree);
int			count_pipes(t_tree_token *tree);
int			**create_double_fd(int process_num);
t_pipes		*init_pipes(t_tree_token *tree);
void		create_pipes(t_pipes *pipes);
void		free_double_array(int **double_array);
int			process_parent(t_pipes *pipes);
int			pipe_multi_process(t_tree_token *tree, char **env, t_data *data);
int			process_child(int i, t_pipes *pipes, t_pipe_cmds *cmd_lst,
				char **env, t_data *data);
void		free_pipes_struct(t_pipes *pipes);

int			redirect_infile(char *filename);
int			redirect_outfile(char *filename);
int			redirect_append(char *filename);
int			redirect_io(t_tree_token *token, t_pipes *pipes, t_data *data);
int redirect_one_cmd(t_tree_token *token);
int redirect_heredoc(char *delimeter);

/* -------------------------------------------------------------------------- */
/*                                  build_in                                  */
/* -------------------------------------------------------------------------- */
int			ft_strcmp(const char *s1, const char *s2);
bool		is_buildin(t_tree_token *tree);
int			exec_buildin(t_tree_token *tree);
int			ft_echo(t_tree_token *tree);
int			ft_pwd(t_tree_token *tree);

/* -------------------------------------------------------------------------- */
/*                                     free                                   */
/* -------------------------------------------------------------------------- */
void		free_program(t_data *data);
void		free_ast(t_tree_token *node);
void		free_file_list(t_file *file);
void		free_all_exit(t_data *data, t_pipes *pipes);
/* -------------------------------------------------------------------------- */
/*                                    debug                                   */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                                error message                               */
/* -------------------------------------------------------------------------- */
void    print_error_msg(char *error_msg, int errno);



#endif