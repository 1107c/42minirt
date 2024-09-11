/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:37:23 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/11 19:37:23 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	*lst_new(t_type type)
{
	if (type == LIGHT)
		return (init_light());
	else
		return (init_fig());
}

void	*lst_last(void *lst, t_type type)
{
	t_fig	*fig;
	t_light	*light;

	if (!lst)
		return (NULL);
	if (type == FIG)
	{
		fig = (t_fig *)lst;
		if (!fig->next)
			return ((void *)fig);
		return (lst_last(fig->next, type));
	}
	light = (t_light *)lst;
	if (!light->next)
		return ((void *)light);
	return (lst_last(light->next, type));
}

void	*lst_addback(t_rt *rt, t_type type)
{
	void	*lst;
	void	*alloc;

	alloc = lst_new(type);
	if (!alloc)
		return (NULL);
	if (type == LIGHT)
	{
		lst = lst_last(rt->light, type);
		if (!lst)
			rt->light = alloc;
		else
			((t_light *)lst)->next = (t_light *)alloc;
		rt->light_cnt++;
	}
	else
	{
		lst = lst_last(rt->fig, type);
		if (!lst)
			rt->fig = alloc;
		else
			((t_fig *)lst)->next = (t_fig *)alloc;
		rt->fig_cnt++;
	}
	return (alloc);
}
