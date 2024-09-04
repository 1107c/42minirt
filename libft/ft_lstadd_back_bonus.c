/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:41:05 by myeochoi          #+#    #+#             */
/*   Updated: 2024/03/01 13:31:41 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	**next_node;

	if (!(*lst))
		*lst = new;
	else
	{
		next_node = &((*lst)->next);
		ft_lstadd_back(next_node, new);
	}
}
