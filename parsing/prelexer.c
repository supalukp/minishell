/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prelexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:08:52 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/12 15:43:42 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

char	*extract_quoted(const char *line, int *i)
{
	char	quote_char;
	int		start;
	int		len;
	char	*content;

	quote_char = line[*i]; // Save quote_char (' or ")
	(*i)++;
	start = *i; // Begining of Quote content
	while (line[*i] && line[*i] != quote_char)
		(*i)++; // Keep i++ until find closing quote
	len = *i - start;
	content = malloc(sizeof(char) * (len + 1));
    if (!content)
    {
        return (NULL);
    }
    ft_strncpy(content, line + start, len); // copy content between quotes
	content[len] = '\0';
	if (line[*i] == quote_char)
		(*i)++;
	return (content);
}

char	*wrap_merged(char *merged, char quote, int count)
{
	char	wrapper[2];
	char	*res;

	res = NULL;
	if (count == 1) // if only one count --> use the same quote
	{
		wrapper[0] = quote;
		wrapper[1] = '\0';
		append_str(&res, wrapper);
		append_str(&res, merged);
		append_str(&res, wrapper);
	}
	else
	{
		append_str(&res, "'");
		append_str(&res, merged);
		append_str(&res, "'");
	}
	free(merged);
	return (res);
}

char	*handle_quotes(const char *line, int *i)
{
	char	*merged;
	char	*tmp;
	char	first_quote;
	int		count;
	int		start;

	count = 0;
	first_quote = '\0';
	merged = NULL;
	while (line[*i] && line[*i] != ' ')
	{
		if (is_quote(line[*i]))
		{
			if (first_quote == '\0')
				first_quote = line[*i];
			tmp = extract_quoted(line, i);
			count++;
		}
		else
		{
			start = *i;
			while (line[*i] && line[*i] != ' ' && !is_quote(line[*i]))
				(*i)++;
			tmp = malloc(*i - start + 1);
            if (!tmp)
                return (NULL);
			ft_strncpy(tmp, line + start, *i - start);
			tmp[*i - start] = '\0';
		}
		append_str(&merged, tmp);
		free(tmp);
	}
	if (first_quote)
		return (wrap_merged(merged, first_quote, count));
	else
		return (merged);
}

char	*merge_quotes(const char *line)
{
	int		i;
	char	*result;
	char	*part;

	i = 0;
	result = NULL;
	if (!line)
		return (NULL);
	while (line[i])
	{
		while (line[i] == ' ')
		{
			append_str(&result, " ");
			i++;
		}
		part = handle_quotes(line, &i);
		append_str(&result, part);
		free(part);
	}
	return (result);
}

// int	main(void)
// {
// 	char	**split;
// 	char	line[] = "'e'\"c\"ho \"hello\" | rev";
//     // char	line[] = "echo \"helloworls\"";
// 	char	*res;

// 	res = merge_quotes(line);
// 	printf("%s\n", res);
//     free(res);
// 	// printf("%d\n", count_char_in_quote("sds"));
// 	// split = ft_split(line, ' ');
// 	// int i = 0;
// 	// while (split[i])
// 	// {
// 	//     printf("%s\n", split[i]);
// 	//     i++;
// 	// }
// 	return (0);
// }
