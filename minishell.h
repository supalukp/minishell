/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:45:37 by spunyapr          #+#    #+#             */
/*   Updated: 2025/04/22 18:28:25 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_type
{
	CMD,
	ARG,
	PIPE,
	OR,
	AND,
	HEREDOC,
	APPEND,
	INFILE,
	OUTFILE,
}					t_type;

typedef struct s_token
{
	char			*name;
	t_type			type;
	struct s_token	*next;
}					t_token;

typedef struct s_branch
{
	t_token			*first_token;
	struct s_branch	*next;
	int				rank;
}					t_branch;

typedef struct s_program
{
	// branch_count include the pipes and sign
	int				branch_count;
	t_branch		*first_branch;

	// Information
	int				pipes;
	int				logic_and;
	int				logic_or;
	int				here_doc;
	int				append;

	// Addresses
	char			*infile_name;
	char			*outfile_name;

	// track last execution
	int				last_exit_status;
}					t_program;

#endif