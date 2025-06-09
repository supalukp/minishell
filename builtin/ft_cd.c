/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:06:37 by syukna            #+#    #+#             */
/*   Updated: 2025/06/09 15:38:41 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	ft_cd(t_tree *tree)
{
	int		rtn;
	char	*home;

	home = getenv("HOME");
	if (!tree->cmd_line->next)
		rtn = chdir(home);
	else
		rtn = chdir(tree->cmd_line->next->content);
	if (rtn == -1)
	{
		ft_putstr_fd("cd: invalid path\n", 2);
		return (1);
	}
	return (0);
}
