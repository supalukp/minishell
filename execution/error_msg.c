/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:51:48 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/24 09:21:21 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void    print_file_err(char *filename, int errnum)
{
    write(STDERR_FILENO, "minishell: ", 12);
    write(STDERR_FILENO, filename, strlen(filename));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, strerror(errnum), strlen(strerror(errnum)));
    write(STDERR_FILENO, "\n", 1);
}
