/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:31:56 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/06 11:22:10 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "headings.h"

/* -------------------------------------------------------------------------- */
/*                                  Function                                  */
/* -------------------------------------------------------------------------- */

// void execute_buidin(t_branch *branch);
// void each_branch_execute(t_branch *branch);
// void execute_external(t_branch *branch);
// void main_execution(t_program *prog);

/* -------------------------------------------------------------------------- */
/*                           init_input (hard code)                           */
/* -------------------------------------------------------------------------- */
void one_cmd(t_token **tree);
void	pipe_simple_input(t_token **tree); // ls-al | wc -l
void	pipe_triple_input(t_token **tree);
void	free_ast(t_token **node);
/* -------------------------------------------------------------------------- */
/*                                  execution                                 */
/* -------------------------------------------------------------------------- */

int		main_execution(t_token *tree, char **env);
char	*find_executable(char **all_path, char *command);
char	*get_path(char *command, char **envp);
void	free_matrix(char **matrix);
int		simple_command_process(t_token *tree, char **env);
int		pipe_process(t_token *tree, char **env);
void	print_ast(t_token *node);

/* -------------------------------------------------------------------------- */
/*                                  build_in                                  */
/* -------------------------------------------------------------------------- */
bool	is_buildin(char *args);
int		exec_buildin(char *args);
int		ft_echo(char *args);
int		ft_pwd(void);

/* -------------------------------------------------------------------------- */
/*                                  debuging                                  */
/* -------------------------------------------------------------------------- */
void	check_if_buildin(t_token *tree);

#endif