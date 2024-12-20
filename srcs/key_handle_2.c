/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 06:21:04 by myeochoi          #+#    #+#             */
/*   Updated: 2024/09/16 06:30:28 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_vector	fig_light_translate_module(int move, int dir, t_vector vec);

void	fig_light_translate(int keycode, t_fig *fig, t_light *light)
{
	if (keycode == NUM_UP && fig)
		fig->xyz = fig_light_translate_module(10, 1, fig->xyz);
	else if (keycode == NUM_DOWN && fig)
		fig->xyz = fig_light_translate_module(-10, 1, fig->xyz);
	else if (keycode == NUM_LEFT && fig)
		fig->xyz = fig_light_translate_module(10, 0, fig->xyz);
	else if (keycode == NUM_RIGHT && fig)
		fig->xyz = fig_light_translate_module(-10, 0, fig->xyz);
	else if (keycode == NUM_FRONT && fig)
		fig->xyz = fig_light_translate_module(10, 2, fig->xyz);
	else if (keycode == NUM_BACK && fig)
		fig->xyz = fig_light_translate_module(-10, 2, fig->xyz);
	else if (keycode == NUM_UP && light)
		light->xyz = fig_light_translate_module(10, 1, light->xyz);
	else if (keycode == NUM_DOWN && light)
		light->xyz = fig_light_translate_module(-10, 1, light->xyz);
	else if (keycode == NUM_LEFT && light)
		light->xyz = fig_light_translate_module(10, 0, light->xyz);
	else if (keycode == NUM_RIGHT && light)
		light->xyz = fig_light_translate_module(-10, 0, light->xyz);
	else if (keycode == NUM_FRONT && light)
		light->xyz = fig_light_translate_module(10, 2, light->xyz);
	else if (keycode == NUM_BACK && light)
		light->xyz = fig_light_translate_module(-10, 2, light->xyz);
	update_cy_co(fig);
}

t_vector	fig_light_translate_module(int move, int dir, t_vector vec)
{
	if (dir == 0)
		return (init_vector(vec.x + move, vec.y, vec.z));
	if (dir == 1)
		return (init_vector(vec.x, vec.y + move, vec.z));
	if (dir == 2)
		return (init_vector(vec.x, vec.y, vec.z + move));
	return (init_vector(0, 0, 0));
}

void	update_cy_co(t_fig *fig)
{
	if (!fig || fig->type == PLANE || fig->type == SPHERE)
		return ;
	else if (fig->type == CYLINDER)
		fig->top = add_vec(fig->xyz, mul_vec(fig->normal_vec, \
						fig->height));
	else if (fig->type == CONE)
		fig->top = add_vec(fig->xyz, mul_vec(fig->normal_vec, \
						2 * fig->height));
}

void	key_light(int keycode, t_rt *rt)
{
	if (keycode == KEY_F)
		rt->fast *= -1;
	if (!rt->selected_light && keycode == KEY_LIGHT)
	{
		rt->selected_light = rt->light;
		rt->selected_light->is_click *= -1;
	}
	else if (keycode == KEY_LIGHT)
	{
		rt->selected_light->is_click *= -1;
		if (!rt->selected_light->next)
			rt->selected_light = rt->light;
		else
			rt->selected_light = rt->selected_light->next;
		rt->selected_light->is_click *= -1;
	}
	if (rt->selected && keycode == KEY_LIGHT)
	{
		rt->selected->rgb = rt->selected->rgb2;
		rt->selected->is_click *= -1;
		rt->selected = NULL;
	}
}

void	fig_rotate(int keycode, t_rt *rt)
{
	if (!rt->selected)
		return ;
	if (keycode == NUM_ROT_X)
	{
		rt->selected->normal_vec = add_vec(mul_vec(rt->selected->right_vec, \
		sin(ANG * 20)), mul_vec(rt->selected->normal_vec, cos(ANG * 20)));
		rt->selected->right_vec = cross_product(rt->selected->up_vec, \
		rt->selected->normal_vec);
	}
	else if (keycode == NUM_ROT_Y)
	{
		rt->selected->normal_vec = add_vec(invert_vec(mul_vec(rt->selected->\
		up_vec, sin(ANG * 20))), mul_vec(rt->selected->normal_vec, \
		cos(ANG * 20)));
		rt->selected->up_vec = cross_product(rt->selected->normal_vec, \
		rt->selected->right_vec);
	}
	update_cy_co(rt->selected);
}
