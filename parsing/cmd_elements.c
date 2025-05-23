/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:44:08 by syukna            #+#    #+#             */
/*   Updated: 2025/05/23 18:06:04 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

int	get_element_len(char *line, int quoted)
{
	int i;
	char	end_letter;

	i = 1;
	if (quoted == 2)
		end_letter = '"';
	else if (quoted == 1)
		end_letter = '\'';
	else
		end_letter = ' ';
	while (line[i] != end_letter && line[i])
		i++;
	return (i);
}

char *	get_element(char *line, int quoted, int len)
{
	char	*rtnstr;
	int		i;
	int		j;
	
	i = 0;
	if (quoted >= 1)
		j = 1;
	else
		j = 0;
	rtnstr = ft_calloc(len, sizeof(char));
	while (i < len - 1)
	{
		rtnstr[i] = line[i + j];
		i++;
	}
	return (rtnstr);
}
size_t	remove_cmd_element_len(t_tree_token *cmd_line, int quoted)
{
	size_t	rmlen;
	char	end_letter;

	rmlen = 1;
	if (quoted == 2)
		end_letter = '"';
	else if (quoted == 1)
		end_letter = '\'';
	else
		end_letter = ' ';
	while (cmd_line->content[rmlen] != end_letter && cmd_line->content[rmlen])
		rmlen++;
	rmlen++;
	while (cmd_line->content[rmlen] == ' ' && cmd_line->content[rmlen])
		rmlen++;
	return (rmlen);
}
void	remove_cmd_element(t_tree_token *cmd_line, int quoted)
{
	size_t rmlen;
	int i;
	char	*rtnstr;

	i = 0;
	rmlen = remove_cmd_element_len(cmd_line, quoted);
	printf("removing length = |%zu|\n", rmlen);
	if (rmlen >= ft_strlen(cmd_line->content))
	{
		free(cmd_line->content);
		cmd_line->content = NULL;
	}
	else 
	{
		rtnstr = ft_calloc(ft_strlen(cmd_line->content) - rmlen + 1, sizeof(char));
		while (cmd_line->content[i + rmlen])
		{
			rtnstr[i] = cmd_line->content[rmlen + i];
			i++;
		}
		free(cmd_line->content);
		cmd_line->content = rtnstr;
		printf("tmpstr = |%s|\n", rtnstr);
		split_cmd_elements(cmd_line);
	}
}

void	add_cmd_element(t_tree_token *cmd_line, int quoted, int len)
{
	t_cmd_element	*element;
	t_cmd_element	*eltmp;

	element = malloc(sizeof(t_cmd_element));
	element->quoted = quoted;
	element->next = NULL;
	element->content = get_element(cmd_line->content, quoted, len);
	if (!cmd_line->cmd_line)
		cmd_line->cmd_line = element;
	else
	{
		eltmp = cmd_line->cmd_line;
		while (eltmp->next)
			eltmp = eltmp->next;
		eltmp->next = element;
	}
}

void	handle_cmd_element(t_tree_token *cmd_line, int quoted)
{
	int len;

	len = get_element_len(cmd_line->content, quoted);
	if (quoted == 0)
		len++;
	add_cmd_element(cmd_line, quoted, len);
	remove_cmd_element(cmd_line, quoted);
	// if (cmd_line->content[i])
	// 	handle_cmd_element(t_tree_token *cmd_line, int quoted)
	printf("handle cmd element | quotes: %d | len: %d\n", quoted, len);
}

void	split_cmd_elements(t_tree_token *cmd_line)
{
	int i;
	char *tmpstr;

	i = 0;
	tmpstr = ft_strtrim(cmd_line->content, " ");
	free(cmd_line->content);
	cmd_line->content = tmpstr;
	if (tmpstr[i])
	{
		if (tmpstr[i] == '"')
			handle_cmd_element(cmd_line, 2);
		else if (tmpstr[i] == '\'')
			handle_cmd_element(cmd_line, 1);
		else
			handle_cmd_element(cmd_line, 0);
	}
}



// static int	countchar(char const *s, char c)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (s[i] == c)
// 		i++;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] != c && (i == 0 || s[i - 1] == c))
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }




// // Counting the length of each string
// static int	getstrlen(char const *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0' && (char)s[i] != c)
// 		i++;
// 	i++;
// 	return (i);
// }

// static void	free_rtnlist(char **rtnlist)
// {
// 	int	i;

// 	i = 0;
// 	while (rtnlist[i])
// 		free(rtnlist[i++]);
// 	free(rtnlist);
// }

// static char	**split_logic(char **rtnlist, const char *s, char c, int count)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;
// 	j = 0;
// 	while (j < count)
// 	{
// 		len = getstrlen((char *)&s[i], c);
// 		rtnlist[j] = ft_calloc(len, sizeof(char));
// 		if (!rtnlist[j])
// 		{
// 			free_rtnlist(rtnlist);
// 			return (NULL);
// 		}
// 		ft_strlcpy(rtnlist[j], &s[i], len);
// 		i += len;
// 		while ((char)s[i] == c)
// 			i++;
// 		j++;
// 	}
// 	return (rtnlist);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**rtnlist;
// 	int		i;
// 	int		count;

// 	if (!s)
// 		return (NULL);
// 	if (s[0] == '\0')
// 	{
// 		rtnlist = ft_calloc(1, sizeof(char *));
// 		if (!rtnlist)
// 			return (NULL);
// 		rtnlist[0] = NULL;
// 		return (rtnlist);
// 	}
// 	i = 0;
// 	while (s[i] == c)
// 		i++;
// 	count = countchar(&s[i], c);
// 	rtnlist = ft_calloc(count + 1, sizeof(char *));
// 	if (!rtnlist)
// 		return (NULL);
// 	return (split_logic(rtnlist, &s[i], c, count));
// }
