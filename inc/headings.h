/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:48:37 by syukna            #+#    #+#             */
/*   Updated: 2025/07/17 10:55:45 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADINGS_H
# define HEADINGS_H
# define _POSIX_C_SOURCE 200809L
# define ECHOCTL 0001000

/* ************************************************************************** */
/* ***************************EXTERNAL LIBRARIES***************************** */
/* ************************************************************************** */

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

/* ************************************************************************** */
/* ***************************INTERNAL LIBRARIES***************************** */
/* ************************************************************************** */

# include "../libft/libft.h"
# include "execution.h"
# include "functions.h"
# include "signals.h"
# include "structures.h"

#endif