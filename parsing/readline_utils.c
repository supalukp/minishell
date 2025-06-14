/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:50:08 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/14 23:31:15 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

char	*build_prompt(int exit_status)
{
    char *exit_str;
    char *tmp;
    char *res;
    
    exit_str = ft_itoa(exit_status);
    tmp = ft_strdup("minishell[");
    res = ft_strjoin(tmp, exit_str);
    free(tmp);
    free(exit_str);
    tmp = ft_strdup("]> ");
    exit_str = ft_strjoin(res, tmp);
    free(tmp);
    free(res);
    return (exit_str);
}
