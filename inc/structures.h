/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:48:43 by syukna            #+#    #+#             */
/*   Updated: 2025/04/30 10:57:06 by syukna           ###   ########.fr       */
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
	PAREN_LEFT,
	PAREN_RIGHT,
	APPEND,
	HEREDOC,
	INFILE,
	OUTFILE
}			t_type;

typedef struct s_token
{
	char		*name; // "&&"
	t_type	type; // AND
	bool		operator; // 1
	struct s_token	*left; // token "ls -a"
	struct s_token	*right; // NULL
}			t_token;

#endif