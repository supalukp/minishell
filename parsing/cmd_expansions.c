/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:11:57 by syukna            #+#    #+#             */
/*   Updated: 2025/06/17 20:07:37 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

char	*find_expansion_match(const char *search, t_env *lst)
{
	while (lst)
	{
		if (ft_strlen(search) == ft_strlen(lst->env_name))
		{
			if (ft_strncmp(search, lst->env_name, ft_strlen(search)) == 0)
				return (lst->env_variable);
		}
		lst = lst->next;
	}
	return ("");
}

void	trim_space(t_cmd_element *cmd)
{
	int		i = 0; 
	int		j = 0;
	int		in_word = 0;
	char	*new_str;
	
	if (!cmd->quoted || !cmd->content)
		return ;
	new_str = ft_calloc(strlen(cmd->content) + 1, sizeof(char));
	if (!new_str)
		return ;
	while (cmd->content[i] == ' ')
		i++;
	while (cmd->content[i])
	{
		if (cmd->content[i] == ' ')
		{
			if (in_word)
				new_str[j++] = ' ';
			in_word = 0;
		}
		else
		{
			new_str[j++] = cmd->content[i];
			in_word = 1;
		}
		i++;
	}
	if (j > 0 && new_str[j - 1] == ' ')
		j--;
	new_str[j] = '\0';
	free(cmd->content);
	cmd->content = new_str;
}

void	exchange_expansion_values(t_cmd_element *el, char *new, int i, int len)
{
	char	*rtnstr;
	int		j;
	int		y;
	
	j = 0;
	y = 0;
	rtnstr = ft_calloc(len + 1, sizeof(char));
	while (j < i)
	{
		rtnstr[j] = el->content[j];
		j++;
	}
	while (new[y])
		rtnstr[j++] = new[y++];
	i++;
	while (ft_isalnum(el->content[i]) || el->content[i] == '_')
		i++;
	if (el->expand_curly_brackets == 2 && el->content[i] == '}')
		i++;
	while (el->content[i])
		rtnstr[j++] = el->content[i++];
	free(el->content);
	el->content = rtnstr;
	trim_space(el);
}

int	current_pos_dollar(char *line, int count)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (j == count)
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

void	replace_expansion(t_cmd_element *line, t_env *lst, int *count)
{
	int 	i;
	int		j;
	int		len;
	char	*searchword;
	char	*rtnvalue;
	int		slashed;

	j = 0;
	slashed = 0;
	i = current_pos_dollar(line->content, *count);
	if (i == -1 || *count >= counterchar(line->content, '$'))
		return ;
	if (!line->content[i + 1] || line->content[i + 1] == ' ')
		(*count)++;
	if ((line->content[i + 1] && includedchar(line->content[i + 1], "$? ")) || !line->content[i + 1])
		return ;
	if (i > 0 && line->content[i - 1] == '\\')
	{
		slashed = 1;
		(*count)++;
		memmove(&line->content[i - 1], &line->content[i], strlen(&line->content[i]) + 1);
		i--;
	}
	else if (line->content[i + 1] == '{')
	{
		line->expand_curly_brackets = 2;
		memmove(&line->content[i + 1], &line->content[i + 2], strlen(&line->content[i + 2]) + 1);
	}
	i++;
	while (ft_isalnum(line->content[i + j]) || line->content[i + j] == '_')
		j++;
	searchword = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(searchword, &line->content[i], j + 1);
	rtnvalue = find_expansion_match(searchword, lst);
	len = ft_strlen(line->content) - j + ft_strlen(rtnvalue) ;
	i--;
	free(searchword);
	if (slashed != 1)
		exchange_expansion_values(line, rtnvalue, i, len);
}

int	counterchar(char const *s1, char letter)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s1[i] == letter)
			j++;
		i++;
	}
	return (j);
}

int	add_expansions(t_tree *node, t_env *lst, t_data *request)
{
	t_cmd_element	*cmd;
	int				expansions;
	int				count;

	cmd = node->cmd_line;
	count = 0;
	while (cmd)
	{
		add_tild(cmd, lst);
		expansions = counterchar(cmd->content, '$');
		while (includedchar('$', cmd->content) && cmd->quoted != 1 && count < counterchar(cmd->content, '$'))
		{
			special_dollar_sign(cmd, lst, &count, request->last_exit);
			replace_expansion(cmd, lst, &count);
		}
		cmd = cmd->next;
		count = 0;
	}
	return (0);
}
