/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:51:19 by spunyapr          #+#    #+#             */
/*   Updated: 2025/02/06 13:20:22 by spunyapr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = *lst;
	if (!*lst || !del)
		return ;
	while (ptr)
	{
		tmp = ptr->next;
		del(ptr->content);
		free(ptr);
		ptr = tmp;
	}
	*lst = NULL;
}
