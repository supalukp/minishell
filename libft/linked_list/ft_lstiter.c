/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syukna <syukna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:38:27 by syukna            #+#    #+#             */
/*   Updated: 2025/01/23 13:47:01 by syukna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;
	t_list	*next;

	if (!lst || !f)
		return ;
	temp = lst;
	while (temp->next)
	{
		next = temp->next;
		(*f)(temp->content);
		temp = next;
	}
	(*f)(temp->content);
	return ;
}
