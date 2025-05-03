/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:48:43 by syukna            #+#    #+#             */
/*   Updated: 2025/05/03 18:28:16 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "headings.h"
# include <stdbool.h>

typedef enum e_type
{
	CMD,
	PIPE,
	AND,
	OR,
	APPEND,
	HEREDOC,
	INFILE,
	OUTFILE,
	INVALID
}			t_type;

typedef struct s_token
{
	char			*content; // "&&"
	t_type			type; // AND
	// int				quoted; // 0 when no quotes, 1 when single, 2 when double
	struct s_token	*left; // token "ls -a"
	struct s_token	*right; // NULL
	// ADD LINKED LIST OF INPUT AND OUTPUT FILES
}					t_token;

typedef struct s_data
{
	t_token			AST;
	// ADD LINKED LIST OF ENV
}					t_data;

// T_DATA IS WHAT I WILL SEND YOU

#endif