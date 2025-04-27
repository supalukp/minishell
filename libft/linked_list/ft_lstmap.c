/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:17:56 by syukna            #+#    #+#             */
/*   Updated: 2025/01/23 13:47:05 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new_list;

	if (!lst || !del || !f)
		return (NULL);
	new_list = NULL;
	tmp = NULL;
	while (lst)
	{
		tmp = malloc(sizeof(t_list));
		if (!tmp)
			return (ft_lstclear(&new_list, del), NULL);
		tmp->content = f(lst->content);
		tmp->next = NULL;
		ft_lstadd_back(&new_list, tmp);
		lst = lst->next;
	}
	return (new_list);
}
