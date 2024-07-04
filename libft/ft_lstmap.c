/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:53:06 by ksuh              #+#    #+#             */
/*   Updated: 2024/05/17 15:02:29 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list	*dest;
	t_list	*node;

	if (!lst || !f)
		return (0);
	dest = ft_lstnew(f(lst->content));
	if (!dest)
		return (0);
	lst = lst->next;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
		{
			ft_lstclear(&dest);
			return (0);
		}
		ft_lstadd_back(&dest, node);
		lst = lst->next;
	}
	return (dest);
}
