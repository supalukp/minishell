/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:44:02 by spunyapr          #+#    #+#             */
/*   Updated: 2025/02/26 11:53:18 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

char	*split_next_line(char *lines, char *buf, int i);
char	*get_buf(int fd, int *status, int i);
char	*get_next_line(int fd);
int		find_char(char *str, char c);
void	ft_st_bzero(char *str);

#endif