/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:31:56 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/12 18:09:26 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "headings.h"
# include "structures.h"

/* -------------------------------------------------------------------------- */
/*                                     env                                    */
/* -------------------------------------------------------------------------- */
void		ft_lstadd_env_back(t_env **lst, t_env *new);
char		**split_env(char *env);
t_env		*create_env_node(char *env_variable);
t_env		*create_own_env(void);
t_env		*env_init(char **env);
void		print_env(t_env *lst);
void		free_env(t_env *env_lst);
t_env		*create_single_node(char *env_name, char *env_variable);
char		*join_key_value(t_env *env_node);
char		**convert_env_lst_double_arrays(t_env *env_lst);

/* -------------------------------------------------------------------------- */
/*                           init_input (hard code)                           */
/* -------------------------------------------------------------------------- */
void		one_cmd(t_tree **tree);
void		try_one_cmd(t_tree **tree);
void		pipe_simple_input(t_tree **tree);
void		print_ast(t_tree *node);
void		init_s_main(t_data **data, t_tree *tree, char **env);
void		double_pipes_input(t_tree **tree);
void		triple_pipes_input(t_tree **tree);
void		quadruple_pipes_input(t_tree **tree);
void		complex_pipe_input(t_tree **tree);
void		and_two_cmd(t_tree **tree);
/* -------------------------------------------------------------------------- */
/*                                  execution                                 */
/* -------------------------------------------------------------------------- */
char		*find_executable(char **all_path, char *command);
char		*get_path(char *command, char **envp);
void		free_matrix(char **matrix);
char		**combine_cmdline(t_cmd_element *args);
int			main_execution(t_tree *tree, t_data *data);
int			external_single(t_tree *tree, t_data *data);
// int			external_single(t_tree *tree, char **env);
int			external_cmd_process(t_tree *tree, t_data *data);
int			pipe_process(t_tree *tree, char **env, t_data *data);
int			command_not_found(char **args);
void		child_execution(char *paths, char **args, char **env);
int			wait_and_clean(int exit_status, pid_t pid, char **args,
				char *paths);

t_pipe_cmds	*create_pipe_cmd_node(t_tree *token);
void		ft_lstadd_cmd_front(t_pipe_cmds **lst, t_pipe_cmds *new);
t_pipe_cmds	*create_cmd_lst(t_tree *tree);
int			exec_cmd_line(t_tree *tree, t_data *data, int exit_status);
int prepare_exec_path(char **args, char **env, char **path);
/* -------------------------------------------------------------------------- */
/*                                    pipes                                   */
/* -------------------------------------------------------------------------- */

void		close_unused_pipes(int i, t_pipes *pipes);
void		setup_inout_first(t_pipes *pipes);
void		setup_inout_last(t_pipes *pipes);
void		setup_inout(int i, t_pipes *pipes);
t_pipe_cmds	*create_pipe_cmd_node(t_tree *token);
void		ft_lstadd_cmd_front(t_pipe_cmds **lst, t_pipe_cmds *new);
t_pipe_cmds	*create_cmd_lst(t_tree *tree);
int			count_pipes(t_tree *tree);
int			**create_double_fd(int process_num);
t_pipes		*init_pipes(t_tree *tree);
void		create_pipes(t_pipes *pipes);
void		free_double_array(int **double_array);
int			process_parent(t_pipes *pipes);
int			pipe_multi_process(t_tree *tree, t_data *data);
int			process_child(int i, t_pipes *pipes, t_pipe_cmds *cmd_lst,
				t_data *data);
void		free_pipes_struct(t_pipes *pipes);

int			redirect_infile(char *filename);
int			redirect_outfile(char *filename);
int			redirect_append(char *filename);
int			redirect_io(t_tree *token, t_pipes *pipes, t_data *data);
int			redirect_one_cmd(t_tree *token);
int			collect_heredoc_input(char *delimeter);
char		*create_random_filename(void);
// int redirect_heredoc(int fd_heredoc);
int			redirect_heredoc(char *delimiter);

/* -------------------------------------------------------------------------- */
/*                                  build_in                                  */
/* -------------------------------------------------------------------------- */
int			no_argument(t_tree *tree);
int			ft_strcmp(const char *s1, const char *s2);
bool		is_buildin(t_tree *tree);
int			exec_buildin(t_tree *tree, t_data *data);
int			ft_echo(t_tree *tree);
int			ft_pwd(t_tree *tree);
int			ft_cd(t_tree *tree);
int			ft_exit(t_tree *tree, int exit_status);
int			ft_env(t_tree *tree, t_data *data);
t_env		**ascii_env_lst(t_data *data);
int			print_export_no_option(t_data *data);
int			count_env_node(t_env *env_lst);
int			ft_export(t_tree *tree, t_data *data);
int			process_arguments(t_tree *tree, t_data *data);
int			create_only_key(t_cmd_element *args, t_data *data);
int			create_key_value(t_cmd_element *args, t_data *data);
int			process_export(char *args, t_data *data);
int			not_valid_identifier(char *function);
int			not_valid_name(char *args, char *function);
int			invalid_option(t_cmd_element *args, char *function);
int			have_equal(char *str);
int			is_plus_equal(char *args);
void		sort_env_lst(int count_env, t_env **env_lst);
t_env		**ascii_env_lst(t_data *data);
int			print_export_no_option(t_data *data);
int			create_new_variable(char *args, t_data *data);
int			add_value_variable(char *args, t_data *data);
int			add_new_variable(char *args, t_data *data);
int			is_exist_variable(char *args, t_data *data);
int			change_value_variable(char *args, t_data *data);
char		**split_env_plus_equal(char *env);
int			unset_variable(char *key, t_data *data);
int			unset_process(t_tree *tree, t_data *data);
int			ft_unset(t_tree *tree, t_data *data);
/* -------------------------------------------------------------------------- */
/*                                     free                                   */
/* -------------------------------------------------------------------------- */
void		free_program(t_data *data);
void		free_ast(t_tree *node);
void		free_file_list(t_file *file);
void		free_all_exit(t_data *data, t_pipes *pipes);
void		free_cmd_lst(t_pipe_cmds *cmd_lst);

/* -------------------------------------------------------------------------- */
/*                                error message                               */
/* -------------------------------------------------------------------------- */
void		stderr_msg(char *err_msg);
void		error_free_pipes(char *err_msg, t_pipes *pipes);
int			perror_free_pipes(char *err_msg, t_pipes *pipes);

#endif