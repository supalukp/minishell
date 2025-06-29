/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:50:54 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/29 13:49:44 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	update_oldpwd(char *old_path, t_env *lst)
{
	while (lst)
	{
		if (ft_strlen(lst->env_name) == 6)
		{
			if (ft_strncmp("OLDPWD", lst->env_name, 6) == 0)
			{
				free(lst->env_variable);
				lst->env_variable = ft_strdup(old_path);
				return ;
			}
		}
		lst = lst->next;
	}
}

char	*update_pwd(char *new_path, t_env *lst)
{
	char	*old_path;
	t_env	*tmp;

	old_path = NULL;
	tmp = lst;
	while (tmp)
	{
		if (ft_strlen(tmp->env_name) == 3)
		{
			if (ft_strncmp("PWD", tmp->env_name, 3) == 0)
			{
				old_path = tmp->env_variable;
				update_oldpwd(old_path, lst);
				tmp->env_variable = new_path;
				free(old_path);
			}
		}
		tmp = tmp->next;
	}
	return ("");
}

int	ft_pwd(t_tree *tree, t_env *lst)
{
	char	*res;

	if (tree && tree->cmd_line && tree->cmd_line->next
		&& tree->cmd_line->next->content)
	{
		if (tree->cmd_line->next->content[0] == '-')
		{
			ft_putstr_fd("pwd: invalid option\n", 2);
			return (2);
		}
	}
	res = getcwd(NULL, 1024);
	if (res == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory: \
			getcwd: cannot access parent directories: \
			No such file or directory\n", 2);
		return (1);
	}
	if (res)
	{
		printf("%s\n", res);
		update_pwd(res, lst);
	}
	return (0);
}
