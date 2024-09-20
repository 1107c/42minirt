/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 06:35:30 by myeochoi          #+#    #+#             */
/*   Updated: 2024/09/18 11:17:25 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	is_selected_fig(t_fig *tmp, int idx, t_rt *rt)
{
	if (tmp->idx == idx && tmp->is_click == -1)
	{
		tmp->rgb = (t_vector){tmp->rgb.x * 0.75, tmp->rgb.y * 0.75, \
		tmp->rgb.z * 0.75, 0};
		tmp->is_click *= -1;
		rt->selected = tmp;
	}
	else if ((tmp->idx != idx && tmp->is_click == 1) || (tmp->idx == idx \
	&& tmp->is_click == 1))
	{
		tmp->rgb = tmp->rgb2;
		tmp->is_click *= -1;
	}
}

int	mouse_handle(int keycode, int x, int y, t_rt *rt)
{
	t_fig	*tmp;
	int		idx;

	tmp = rt->fig;
	idx = rt->map[y][x] - 48;
	if (keycode == 1)
	{
		while (tmp)
		{
			is_selected_fig(tmp, idx, rt);
			if (rt->selected_light)
			{
				rt->selected_light->is_click *= -1;
				rt->selected_light = NULL;
			}
			tmp = tmp->next;
		}
		draw(rt);
	}
	return (0);
}
