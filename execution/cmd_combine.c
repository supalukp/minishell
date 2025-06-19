/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_combine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:11:16 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/19 11:11:53 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static char	**alloc_cmd_array(int count)
{
	char	**res;

	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	return (res);
}

static int	fill_cmd_array(char **res, t_cmd_element *args)
{
	int				i;
	t_cmd_element	*tmp;

	i = 0;
	tmp = args;
	while (tmp)
	{
		res[i] = ft_strdup(tmp->content);
		if (!res[i])
		{
			while (i--)
				free(res[i]);
			free(res);
			return (1);
		}
		tmp = tmp->next;
		i++;
	}
	res[i] = NULL;
	return (0);
}

char	**combine_cmdline(t_cmd_element *args)
{
	char	**res;
	int		count;

	count = count_cmd_element(args);
	if (count == 0)
		return (NULL);
	res = alloc_cmd_array(count);
	if (!res)
		return (NULL);
	if (fill_cmd_array(res, args))
		return (NULL);
	return (res);
}

// char	**combine_cmdline(t_cmd_element *args)
// {
// 	char			**res;
// 	int				count;
// 	int				i;
// 	t_cmd_element	*tmp;

// 	count = count_cmd_element(args);
// 	if (count == 0)
// 		return (NULL);
// 	res = malloc(sizeof(char *) * (count + 1));
// 	i = 0;
// 	tmp = args;
// 	while (tmp)
// 	{
// 		res[i] = ft_strdup(tmp->content);
// 		if (!res[i])
// 		{
// 			while (i--)
// 				free(res[i]);
// 			free(res);
// 			return (NULL);
// 		}
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	res[i] = NULL;
// 	return (res);
// }
