/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:31:56 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 11:35:06 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "headings.h"
# include "structures.h"

/* -------------------------------------------------------------------------- */
/*                                     env                                    */
/* -------------------------------------------------------------------------- */
char		**convert_env_lst_double_arrays(t_env *env_lst);
char		**split_env(const char *env);
char		**split_env_plus_equal(const char *env);
t_env		*create_single_node(const char *env_name, char *env_variable);
t_env		*env_init(char **env);
void		ft_lstadd_env_back(t_env **lst, t_env *new);
t_env		*create_env_node(char *env_variable);
void		print_env(t_env *lst);
void		free_env(t_env *env_lst);
int			count_env_node(t_env *env_lst);

/* -------------------------------------------------------------------------- */
/*                                 redirection                                */
/* -------------------------------------------------------------------------- */
int			save_fd_io(t_tree *node);
int			get_infile(char *filename);
int			get_outfile(char *filename);
int			get_append(char *filename);
int			redirect_heredoc(t_file *file, t_tree *node);
void		safe_close(int *fd);
void		close_save_fd(t_tree *node);
int			failed_dup(int fd);
int			dup_for_pipes(int i, t_tree *node, t_pipes *pipes);
int			dup_for_one_cmd(t_tree *node);
char		*create_random_filename(void);
int			open_tmpfile(char **tmpfile);
int			open_tty(char *tmpfile, int fd_write);
int			handle_heredoc_open_fail(char *tmpfile);
int			clean_exit(char *tmpfile, int fd_write, int fd_tty, int ret);
void		assign_heredoc_fd(t_tree *node, int fd_read);
int			setup_inout_middle(int i, t_pipes *pipes, t_tree *node);
int			setup_inout_last(int i, t_pipes *pipes, t_tree *node);
int			setup_inout_first(t_pipes *pipes, t_tree *node);

/* -------------------------------------------------------------------------- */
/*                                   builtin                                  */
/* -------------------------------------------------------------------------- */
bool		is_builtin(t_tree *tree);
int			exec_builtin(t_tree *tree, t_data *data);
int			ft_cd(t_tree *tree);
int			ft_echo(t_tree *tree);
int			ft_env(t_tree *tree, t_data *data);
int			ft_exit(t_tree *tree, int exit_status);
int			add_value_variable(char *args, t_data *data);
int			add_new_variable(char *args, t_data *data);
int			is_exist_variable(char *args, t_data *data);
int			change_value_variable(char *args, t_data *data);
int			create_new_variable(char *args, t_data *data);
int			no_argument(t_tree *tree);
t_env		**ascii_env_lst(t_data *data);
int			print_export_no_option(t_data *data);
int			have_equal(char *str);
int			is_plus_equal(char *args);
int			not_valid_name(char *args, char *function);
int			invalid_option(t_cmd_element *args, char *function);
int			process_export(char *args, t_data *data);
int			create_key_value(t_cmd_element *args, t_data *data);
int			create_only_key(t_cmd_element *args, t_data *data);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_export(t_tree *tree, t_data *data);
int			ft_pwd(t_tree *tree);
int			ft_unset(t_tree *tree, t_data *data);

/* -------------------------------------------------------------------------- */
/*                                  execution                                 */
/* -------------------------------------------------------------------------- */

// Execution
int			main_execution(t_tree *tree, t_data *data);
int			exec_cmd_line(t_tree *tree, t_data *data, int exit_status);
int			count_cmd_element(t_cmd_element *args);
char		**combine_cmdline(t_cmd_element *args);
int			check_access_path(char *path);
char		*get_program_name(char *path);
int			prepare_exec_path(char **args, char **path, char **env);
char		*get_path(char *command, char **envp);
char		*find_executable(char **all_path, char *command);

// Pipes
int			pipe_multi_process(t_tree *tree, t_data *data);
t_pipes		*init_pipes(t_tree *tree);
void		create_pipes(t_pipes *pipes);
t_pipe_cmds	*create_cmd_lst(t_tree *tree);
int			fork_and_exec_children(t_pipes *pipes, t_data *data);
int			process_parent(t_pipes *pipes);

// Single command
int			external_cmd_process(t_tree *tree, t_data *data);
void		child_execution(char *paths, char **args, char **minishell_env,
				t_data *data);
int			wait_and_clean(int exit_status, pid_t pid, char **args,
				char *paths);
void		backup_std_io(int stdin_backup, int stdout_backup);
int			init_path(char **path, char **args, char **env);
int			external_single(t_tree *tree, t_data *data);

// Error Message
void		print_file_err(const char *filename, int errnum);
int			command_not_found(char **args);
void		stderr_msg(const char *err_msg);
void		error_free_pipes(const char *err_msg, t_pipes *pipes);
int			perror_free_pipes(const char *err_msg, t_pipes *pipes);

// Free
void		free_file_list(t_file *file);
void		free_ast(t_tree *node);
void		free_matrix(char **matrix);
void		free_program(t_data *data);
void		free_pipes(t_pipes *pipes);
void		free_double_array(int **double_array);
void		free_cmd_lst(t_pipe_cmds *cmd_lst);
void		free_pipes_struct(t_pipes *pipes);
void		free_data_pipes(t_data *data, t_pipes *pipes);

#endif