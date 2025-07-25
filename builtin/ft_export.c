/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:34:42 by spunyapr          #+#    #+#             */
/*   Updated: 2025/07/22 16:54:18 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

static int	process_export(char *args, t_data *data)
{
	int	flag;

	flag = 0;
	if (is_plus_equal(args))
		flag = add_value_variable(args, data);
	else if (is_exist_variable(args, data))
		flag = change_value_variable(args, data);
	else
		flag = add_new_variable(args, data);
	return (flag);
}

static int	create_key_value(t_cmd_element *args, t_data *data)
{
	int	flag;

	flag = 0;
	if (have_equal(args->content))
	{
		if (not_valid_name(args->content, "export"))
			flag = 1;
		else
			flag = process_export(args->content, data);
	}
	return (flag);
}

static int	create_only_key(t_cmd_element *args, t_data *data)
{
	int	flag;

	flag = 0;
	if (not_valid_name(args->content, "export"))
		flag = 1;
	else
		flag = create_new_variable(args->content, data);
	return (flag);
}

static int	process_arguments(t_tree *tree, t_data *data)
{
	int				flag;
	t_cmd_element	*args;

	flag = 0;
	args = tree->cmd_line->next;
	if (invalid_option(args, "export"))
		return (2);
	while (args)
	{
		if (have_equal(args->content))
		{
			if (create_key_value(args, data))
				flag = 1;
		}
		else
		{
			if (create_only_key(args, data))
				flag = 1;
		}
		args = args->next;
	}
	return (flag);
}

int	ft_export(t_tree *tree, t_data *data)
{
	if (no_argument(tree))
		return (print_export_no_option(data));
	else
		return (process_arguments(tree, data));
	return (0);
}
