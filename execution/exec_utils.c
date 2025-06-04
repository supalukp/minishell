/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:58:36 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/04 11:45:46 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

char	*find_executable(char **all_path, char *command)
{
	int		j;
	char	*add_slash;
	char	*path_command;

	j = 0;
	while (all_path[j] != NULL)
	{
		add_slash = ft_strjoin(all_path[j], "/");
		if (!add_slash)
			return (free_matrix(all_path), NULL);
		path_command = ft_strjoin(add_slash, command);
		if (!path_command)
			return (free_matrix(all_path), NULL);
		free(add_slash);
		if (access(path_command, F_OK | X_OK) == 0)
		{
			free_matrix(all_path);
			return (path_command);
		}
		free(path_command);
		j++;
	}
	return (free_matrix(all_path), NULL);
}

char	*get_path(char *command, char **envp)
{
	int		i;
	char	**all_path;

	i = 0;
	if (!command || !envp)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			all_path = ft_split(ft_strchr(envp[i], '=') + 1, ':');
			if (!all_path)
				return (NULL);
			return (find_executable(all_path, command));
		}
		i++;
	}
	return (NULL);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_program(t_data *data)
{
	if (data->ast)
		free_ast(data->ast);
	if (data->env)
		free_env(data->env);
	if (data)
		free(data);
}
