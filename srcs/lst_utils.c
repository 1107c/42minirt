/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_xss.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:37:23 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/16 01:45:07 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	*lst_last(void *lst, t_type type);
static void	*lst_new(t_type type);

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

void	free_lst(t_rt *rt)
{
	t_fig	*fig;
	t_light	*light;

	while (rt->fig)
	{
		fig = rt->fig;
		rt->fig = rt->fig->next;
		free(fig);
	}
	while (rt->light)
	{
		light = rt->light;
		rt->light = rt->light->next;
		free(light);
	}
}

void	free_bump(t_bump *bump)
{
	t_bump	*tmp;
	int		i;

	while (bump)
	{
		tmp = bump;
		i = 0;
		while (bump->color_map[i] != 0)
		{
			free(bump->normal_map[i]);
			free(bump->color_map[i]);
			i++;
		}
		free(bump->normal_map);
		free(bump->color_map);
		bump = bump->next;
		free(tmp);
	}
}
