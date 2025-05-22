/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:18:31 by spunyapr          #+#    #+#             */
/*   Updated: 2025/05/22 14:11:30 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define _GNU_SOURCE
// #include <fcntl.h>
#include "../inc/headings.h"

int redirect_heredoc(char *delimeter)
{
    int fd;

    fd = open("/tmp", O_TMPFILE | O_WRONLY, 0600);
    
}