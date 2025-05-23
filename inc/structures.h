/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:48:43 by syukna            #+#    #+#             */
/*   Updated: 2025/04/29 15:20:42 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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
	char		*name;
	t_type	type;
	int			operator;
	struct s_token	*left;
	struct s_token	*right;
}			t_token;

#endif