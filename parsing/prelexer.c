/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prelexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:08:52 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/08 23:10:28 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

// 1. Remove quote / escape and put it in single quotes skip the one that have space
// 2. Expansion

int is_quote(char character)
{
    if (character == '\'' || character == '"')
        return (1);
    else if (character == '"')
        return (2);
    return (0);
}

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    i = 0;
    while (i < n && src[i])
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return (dest);
}

void append_str(char **dest, const char *src) 
{
    int len;
    char *new_str;
    
    if (*dest == NULL) 
        *dest = ft_strdup(src);
    else 
    {
        len = ft_strlen(*dest) + ft_strlen(src) + 1;
        new_str = malloc(len);
        if (!new_str)
            return;
         new_str[0] = '\0';
        ft_strlcat(new_str, *dest, len);
        ft_strlcat(new_str, src, len);
        free(*dest);
        *dest = new_str;
    }
}

char *extract_quoted(const char *line, int *i) 
{
    char quote_char;
    int start;
    int len;
    char *content;
    
    quote_char = line[*i];
    (*i)++;
    start = *i;
    while (line[*i] && line[*i] != quote_char) 
        (*i)++;
    len = *i - start;
    content = malloc(len + 1);
    ft_strncpy(content, line + start, len);
    content[len] = '\0';
    if (line[*i] == quote_char)
        (*i)++;
    return (content);
}

char *merge_adjacent_quotes(const char *line) 
{
    int i;
    int start;
    int len;
    char *spaces;
    char *result;
    char *merged;
    char *token;
    char quote_type;
    int merged_count;
    char this_quote;
    char *part;
    
    i = 0;
    result = NULL;
    while (line[i]) 
    {
        if (isspace(line[i])) 
        {
            start = i;
            while (line[i] && isspace(line[i]))
                i++;
            len = i - start;
            spaces = malloc(len + 1);
            ft_strncpy(spaces, line + start, len);
            spaces[len] = '\0';
            append_str(&result, spaces);
            free(spaces);
        }
        else if (is_quote(line[i])) 
        {
            merged = NULL;
            quote_type = line[i];
            merged_count = 0;
            while (line[i] && is_quote(line[i])) 
            {
                char this_quote = line[i];
                char *part = extract_quoted(line, &i);
                append_str(&merged, part);
                free(part);
                merged_count++;
                if (!line[i] || isspace(line[i]) || !is_quote(line[i]))
                    break;
            }
            if (merged_count == 1) 
            {
                char wrapper[2] = {quote_type, '\0'};
                append_str(&result, wrapper);
                append_str(&result, merged);
                append_str(&result, wrapper);
            } 
            else 
            {
                append_str(&result, "'");
                append_str(&result, merged);
                append_str(&result, "'");
            }
            free(merged);
        }
        else 
        {
            start = i;
            while (line[i] && !isspace(line[i]) && !is_quote(line[i]))
                i++;
            len = i - start;
            token = malloc(len + 1);
            ft_strncpy(token, line + start, len);
            token[len] = '\0';
            append_str(&result, token);
            free(token);
        }
    }
    return (result);
}


int main(void)
{
    char **split;
    char line[] = "echo 'l'\"s -al\"      \"hello\" 'ex'";
    char *res = merge_adjacent_quotes(line);
    printf("%s\n", res);
    // printf("%d\n", count_char_in_quote("sds"));
    // split = ft_split(line, ' ');
    // int i = 0;
    // while (split[i])
    // {
    //     printf("%s\n", split[i]);
    //     i++;
    // }
    return (0);
}