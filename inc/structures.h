/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:48:43 by syukna            #+#    #+#             */
/*   Updated: 2025/04/30 16:02:46 by spunyapr         ###   ########.fr       */
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
}					t_type;

typedef struct s_token
{
	t_type			type;
	char			*name;
	int				op;
	struct s_token	*left;
	struct s_token	*right;
}					t_token;

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}					t_env;

#endif