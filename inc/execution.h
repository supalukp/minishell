/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:31:56 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/09 16:42:22 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "headings.h"

/* -------------------------------------------------------------------------- */
/*                           init_input (hard code)                           */
/* -------------------------------------------------------------------------- */
void	one_cmd(t_tree_token **tree);
void	pipe_simple_input(t_tree_token **tree);
void	print_ast(t_tree_token *node);
void	init_s_main(t_data **data, t_tree_token *tree);
/* -------------------------------------------------------------------------- */
/*                                  execution                                 */
/* -------------------------------------------------------------------------- */
char	*find_executable(char **all_path, char *command);
char	*get_path(char *command, char **envp);
void	free_matrix(char **matrix);
char	**combine_cmdline(t_cmd_element *args);
int		main_execution(t_tree_token *tree, char **env, t_data *root);
int		external_single(t_tree_token *tree, char **env);
int		external_cmd_process(t_tree_token *tree, char **env);
int		pipe_process(t_tree_token *tree, char **env, t_data *data);

/* -------------------------------------------------------------------------- */
/*                                  build_in                                  */
/* -------------------------------------------------------------------------- */
int		ft_strcmp(const char *s1, const char *s2);
bool	is_buildin(char *args);
int		exec_buildin(char *args);
int		ft_echo(char *args);
int		ft_pwd(void);

/* -------------------------------------------------------------------------- */
/*                                     free                                   */
/* -------------------------------------------------------------------------- */
void	free_program(t_data *data);
void	free_ast(t_tree_token **node);

/* -------------------------------------------------------------------------- */
/*                                    debug                                   */
/* -------------------------------------------------------------------------- */
void	check_if_buildin(t_tree_token *tree);

#endif