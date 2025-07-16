/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:06:37 by syukna            #+#    #+#             */
/*   Updated: 2025/07/16 13:48:57 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	ft_cd(t_tree *tree, t_env *lst)
{
	int		rtn;
	char	*home;
	char	*new_path;

	home = getenv("HOME");
	if (!tree->cmd_line->next)
		rtn = chdir(home);
	else
		rtn = chdir(tree->cmd_line->next->content);
	new_path = getcwd(NULL, 1024);
	update_pwd(new_path, lst, 1);
	if (rtn == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(tree->cmd_line->next->content, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}
