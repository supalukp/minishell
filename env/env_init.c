/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:22:18 by spunyapr          #+#    #+#             */
/*   Updated: 2025/06/03 14:52:08 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/headings.h"

void	ft_lstadd_env_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return ;
}

char **split_env(char *env)
{
    char **res;
    int i = 0;

    if (!env)
        return (NULL);
    while (env[i] && env[i] != '=')
        i++;
    res = malloc(sizeof(char *) * 3);
    if (!res)
        return (NULL);
    res[0] = ft_substr(env, 0, i);
    res[1] = ft_substr(env, i + 1, ft_strlen(env) - i - 1);
    res[2] = NULL;
    return (res);
}

char **split_env_plus_equal(char *env)
{
    char **res;
    int i = 0;

    if (!env)
        return (NULL);
    while (env[i] && env[i] != '+')
        i++;
    res = malloc(sizeof(char *) * 3);
    if (!res)
        return (NULL);
    res[0] = ft_substr(env, 0, i);
    res[1] = ft_substr(env, i + 2, ft_strlen(env) - i - 2);
    res[2] = NULL;
    return (res);
}

t_env *create_env_node(char *env_variable)
{
	t_env *node;
    char **variable;
	
    
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
    variable = split_env(env_variable);
    if (!variable[0] || !variable[1])
    {
        free_matrix(variable);
        free(node);
        return (NULL);
    }
	node->env_name = ft_strdup(variable[0]);
    node->env_variable = ft_strdup(variable[1]);
	node->next = NULL;
    free_matrix(variable);
	return (node);
}

t_env *create_own_env(void)
{
    t_env *own_lst;

    own_lst = malloc(sizeof(t_env));
    if (!own_lst)
        return (NULL);
    own_lst->env_name = ft_strdup("OLDPWD");
    own_lst->env_variable = NULL;
    own_lst->next = malloc(sizeof(t_env));
    own_lst->next->env_name = ft_strdup("PWD");
    own_lst->next->env_variable = ft_strdup(getcwd(NULL, 1024));
    own_lst->next->next = malloc(sizeof(t_env));
    own_lst->next->next->env_name = ft_strdup("SHLVL");
    own_lst->next->next->env_variable = ft_strdup("1");
    own_lst->next->next->next = NULL;
    return (own_lst);
}

t_env *env_init(char **env)
{
    t_env *env_lst;
    t_env *tmp;
    int i;
    
    tmp = NULL;
    env_lst = NULL;
    i = 0;
    if (!env || !env[0])
        env_lst = create_own_env(); 
    else
    {
        while (env[i])
        {
            tmp = create_env_node(env[i]);
            if (!tmp)
                return (NULL); // FREE all list malloc before
            ft_lstadd_env_back(&env_lst,tmp);
            i++;
        }
    }
    return (env_lst);
}

void print_env(t_env *lst)
{
    while (lst)
    {
        if (lst->env_variable == NULL)
            lst = lst->next;
        else
        {
            printf("%s=%s\n", lst->env_name, lst->env_variable);
            lst = lst->next;
        }
    }
}

void free_env(t_env *env_lst)
{
	t_env	*tmp;

	while (env_lst)
	{
		tmp = env_lst->next;
        if (env_lst->env_name)
            free(env_lst->env_name);
        if (env_lst->env_variable)
            free(env_lst->env_variable);
        if (env_lst)
		    free(env_lst);
		env_lst = tmp;
	}
}
