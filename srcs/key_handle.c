/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:12:55 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/15 20:27:58 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	key_translate(int keycode, t_rt *rt);
static void	key_rotate(int keycode, t_rt *rt);

t_vector	fig_light_translate_module(int move, int dir, t_vector vec)
{
	if (dir == 0)
		return ((t_vector){vec.x + move, vec.y, vec.z});
	if (dir == 1)
		return ((t_vector){vec.x, vec.y + move, vec.z});
	if (dir == 2)
		return ((t_vector){vec.x, vec.y, vec.z + move});
}

void	fig_light_translate(int keycode, t_rt *rt)
{
	if (keycode == NUM_UP && rt->selected)
		rt->selected->xyz = fig_light_translate_module(10, 1, rt->selected->xyz);
	else if (keycode == NUM_DOWN && rt->selected)
		rt->selected->xyz = fig_light_translate_module(-10, 1, rt->selected->xyz);
	else if (keycode == NUM_LEFT && rt->selected)
		rt->selected->xyz = fig_light_translate_module(10, 0, rt->selected->xyz);
	else if (keycode == NUM_RIGHT && rt->selected)
		rt->selected->xyz = fig_light_translate_module(-10, 0, rt->selected->xyz);
	else if (keycode == NUM_FRONT && rt->selected)
		rt->selected->xyz = fig_light_translate_module(10, 2, rt->selected->xyz);
	else if (keycode == NUM_BACK && rt->selected)
		rt->selected->xyz = fig_light_translate_module(-10, 2, rt->selected->xyz);
	else if (keycode == NUM_UP && rt->selected_light)
		rt->selected_light->xyz = fig_light_translate_module(10, 1, rt->selected_light->xyz);
	else if (keycode == NUM_DOWN && rt->selected_light)
		rt->selected_light->xyz = fig_light_translate_module(-10, 1, rt->selected_light->xyz);
	else if (keycode == NUM_LEFT && rt->selected_light)
		rt->selected_light->xyz = fig_light_translate_module(10, 0, rt->selected_light->xyz);
	else if (keycode == NUM_RIGHT && rt->selected_light)
		rt->selected_light->xyz = fig_light_translate_module(-10, 0, rt->selected_light->xyz);
	else if (keycode == NUM_FRONT && rt->selected_light)
		rt->selected_light->xyz = fig_light_translate_module(10, 2, rt->selected_light->xyz);
	else if (keycode == NUM_BACK && rt->selected_light)
		rt->selected_light->xyz = fig_light_translate_module(-10, 2, rt->selected_light->xyz);
}

void	key_light(int keycode, t_rt *rt)
{
	t_fig *tmp;

	// if (rt->selected)
	// 	rt->selected = NULL;
	rt->light->is_click *= -1;
	rt->selected_light = rt->light;
	if (rt->selected)
	{
		rt->selected->rgb = rt->selected->rgb2;
		rt->selected->is_click *= -1;
		rt->selected = NULL;
	}
	
}

void	fig_light_rotate(int keycode, t_rt *rt)
{
	t_vector	v;

	if (keycode == NUM_ROT_X && rt->selected && rt->selected->type != 1)
	{
		rt->selected->normal_vec = add_vec(mul_vec(rt->selected->right_vec, sin(ANG * 20)), mul_vec(rt->selected->normal_vec, cos(ANG * 20)));
		rt->selected->right_vec = cross_product(rt->selected->up_vec, rt->selected->normal_vec);
	}
	if (keycode == NUM_ROT_Y && rt->selected && rt->selected->type != 1)
	{
		rt->selected->normal_vec = add_vec(invert_vec(mul_vec(rt->selected->up_vec, sin(ANG * 20))), mul_vec(rt->selected->normal_vec, cos(ANG * 20)));
		rt->selected->up_vec = cross_product(rt->selected->normal_vec, rt->selected->right_vec);
	}	
}

void	fig_resize_dia(int keycode, t_rt *rt)
{
	if (keycode == NUM_PLUS && rt->selected)
	{
		if (rt->selected->type == 1)
			rt->selected->diameter += 2;
		else if (rt->selected->type == 2)
			rt->selected->diameter += 2;
	}
	if (keycode == NUM_MINUS && rt->selected && rt->selected->diameter > 3)
	{
		if (rt->selected->type == 1)
			rt->selected->diameter -= 2;
		else if (rt->selected->type == 2)
			rt->selected->diameter -= 2;
	}
}

void	fig_resize_height(int keycode, t_rt *rt)
{
	if (keycode == KEY_PLUS && rt->selected->type == 2)
	{
			rt->selected->height += 2;
	}
	if (keycode == KEY_MINUS && rt->selected->type == 2 && rt->selected->height > 3)
	{
			rt->selected->height -= 2;
	}
}

int	key_handle(int keycode, t_rt *rt)
{
	//printf("keycode: %d\n", keycode);
	if (keycode == KEY_ESC)
		close_all(rt, NULL);
	else if (keycode == KEY_UP || keycode == KEY_DOWN || \
			keycode == KEY_LEFT || keycode == KEY_RIGHT)
		key_rotate(keycode, rt);
	else if (keycode == KEY_W || keycode == KEY_A || \
		keycode == KEY_S || keycode == KEY_D || \
		keycode == KEY_Q || keycode == KEY_E)
		key_translate(keycode, rt);
	else if (keycode == NUM_UP || keycode == NUM_DOWN || \
			keycode == NUM_LEFT || keycode == NUM_RIGHT || \
			keycode == NUM_FRONT || keycode == NUM_BACK)
		fig_light_translate(keycode, rt);
	else if (keycode == KEY_LIGHT)
		key_light(keycode, rt);
	else if (keycode == NUM_ROT_X || keycode == NUM_ROT_Y )
		fig_light_rotate(keycode, rt);
	else if (keycode == NUM_PLUS || keycode == NUM_MINUS)
		fig_resize_dia(keycode, rt);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		fig_resize_height(keycode, rt);
	//printf("%d\n", keycode);
	/*else if (keycode == KEY_R)
		rt_reset(rt);
	else if (keycode == KEY_Z || keycode == KEY_X || \
				keycode == KEY_PLUS || keycode == KEY_MINUS)
		key_scale(keycode, rt);
	else if (keycode == KEY_I || keycode == KEY_P)
		key_project(keycode, rt);
	draw(rt);*/
	clear_image(rt->img);
	draw(rt);
	return (0);
}

void	key_translate(int keycode, t_rt *rt)
{
	if (keycode == KEY_W)
		rt->cam->coords = add_vec(rt->cam->coords, mul_vec(rt->cam->orient_vec, 20));
	else if (keycode == KEY_S)
		rt->cam->coords = add_vec(rt->cam->coords, mul_vec(rt->cam->orient_vec, -20));
	else if (keycode == KEY_A)
		rt->cam->coords = add_vec(rt->cam->coords, mul_vec(rt->cam->right_vec, -20));
	else if (keycode == KEY_D)
		rt->cam->coords = add_vec(rt->cam->coords, mul_vec(rt->cam->right_vec, 20));
	else if (keycode == KEY_Q)
		rt->cam->coords = add_vec(rt->cam->coords, mul_vec(rt->cam->up_vec, 20));
	else if (keycode == KEY_E)
		rt->cam->coords = add_vec(rt->cam->coords, mul_vec(rt->cam->up_vec, -20));
}

void	key_rotate(int keycode, t_rt *rt)
{
	if (keycode == KEY_UP)
		rt->cam->phi += 20;
	else if (keycode == KEY_DOWN)
		rt->cam->phi -= 20;
	else if (keycode == KEY_LEFT)
		rt->cam->theta -= 20;
	else if (keycode == KEY_RIGHT)
		rt->cam->theta += 20;
}
