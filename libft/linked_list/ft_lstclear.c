/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:28:40 by syukna            #+#    #+#             */
/*   Updated: 2025/01/23 13:46:59 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*next;

	if (!lst || !(*lst) || !del)
		return ;
	temp = *lst;
	while (temp->next)
	{
		next = temp->next;
		ft_lstdelone(temp, (*del));
		temp = next;
	}
	ft_lstdelone(temp, (*del));
	*lst = NULL;
	return ;
}
