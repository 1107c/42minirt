/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:12:55 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 13:45:30 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	cam_translate(int keycode, t_rt *rt);
static void	cam_rotate(int keycode, t_rt *rt);

void	fig_resize_dia(int keycode, t_rt *rt)
{
	if (keycode == NUM_PLUS && rt->selected)
	{
			rt->selected->diameter += 2;
			rt->selected->radius_sq = pow(rt->selected->diameter / 2, 2);
		// else if (rt->selected->type == 2)
			// rt->selected->diameter += 2;
		// else if (rt->selected->type == 3)
			// rt->selected->diameter += 2;
	}
	if (keycode == NUM_MINUS && rt->selected && rt->selected->diameter > 3)
	{
		// if (rt->selected->type == 1)
			rt->selected->diameter -= 2;
			rt->selected->radius_sq = pow(rt->selected->diameter / 2, 2);
		// else if (rt->selected->type == 2)
			// rt->selected->diameter -= 2;
		// else if (rt->selected->type == 3)
			// rt->selected->diameter -= 2;
	}
}

void	fig_resize_height(int keycode, t_rt *rt)
{
	if (!rt->selected)
		return ;
	if (keycode == KEY_PLUS && rt->selected->type == 2)
		rt->selected->height += 2;
	if (keycode == KEY_MINUS && rt->selected->type == 2 && \
	rt->selected->height > 3)
		rt->selected->height -= 2;
	if (keycode == KEY_PLUS && rt->selected->type == 3)
		rt->selected->height += 2;
	if (keycode == KEY_MINUS && rt->selected->type == 3 && \
	rt->selected->height > 3)
		rt->selected->height -= 2;
}

int	key_handle(int keycode, t_rt *rt)
{
	if (keycode == 112)
	{
		printf("coords: %lf,%lf,%lf\n", rt->cam->coords.x, rt->cam->coords.y, rt->cam->coords.z);
		printf("orient: %lf,%lf,%lf\n", rt->cam->orient_vec.x, rt->cam->orient_vec.y, rt->cam->orient_vec.z);
	}
	if (keycode == KEY_ESC)
		close_all(rt, NULL);
	else if (keycode == KEY_UP || keycode == KEY_DOWN || \
			keycode == KEY_LEFT || keycode == KEY_RIGHT)
		cam_rotate(keycode, rt);
	else if (keycode == KEY_W || keycode == KEY_A || \
		keycode == KEY_S || keycode == KEY_D || \
		keycode == KEY_Q || keycode == KEY_E)
		cam_translate(keycode, rt);
	else if (keycode == NUM_UP || keycode == NUM_DOWN || \
			keycode == NUM_LEFT || keycode == NUM_RIGHT || \
			keycode == NUM_FRONT || keycode == NUM_BACK)
		fig_light_translate(keycode, rt->selected, rt->selected_light);
	else if (keycode == KEY_LIGHT)
		key_light(keycode, rt);
	else if (keycode == NUM_ROT_X || keycode == NUM_ROT_Y)
		fig_rotate(keycode, rt);
	else if (keycode == NUM_PLUS || keycode == NUM_MINUS)
		fig_resize_dia(keycode, rt);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		fig_resize_height(keycode, rt);
	else if (keycode == KEY_SPACE || keycode == KEY_B || keycode == KEY_N)
		return (key_checkboard_bump(keycode, rt), 0);
	return (draw(rt), 0);
}

void	cam_translate(int keycode, t_rt *rt)
{
	if (keycode == KEY_W)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->orient_vec, 0.3));
	else if (keycode == KEY_S)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->orient_vec, -0.3));
	else if (keycode == KEY_D)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->right_vec, 0.3));
	else if (keycode == KEY_A)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->right_vec, -0.3));
	else if (keycode == KEY_Q)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->up_vec, 0.3));
	else if (keycode == KEY_E)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->up_vec, -0.3));
	rt->cam->screen_origin = init_point(rt->cam);
}

void	cam_rotate(int keycode, t_rt *rt)
{
	if (keycode == KEY_UP)
		rt->cam->phi += 10;
	else if (keycode == KEY_DOWN)
		rt->cam->phi -= 10;
	else if (keycode == KEY_LEFT)
		rt->cam->theta -= 10;
	else if (keycode == KEY_RIGHT)
		rt->cam->theta += 10;
	if (rt->cam->theta >= 180.0)
		rt->cam->theta -= 360.0;
	else if (rt->cam->theta <= -180.0)
		rt->cam->theta += 360.0;
	if (rt->cam->phi >= 180.0)
		rt->cam->phi -= 360.0;
	else if (rt->cam->phi <= -180.0)
		rt->cam->phi += 360.0;
	update_basis(rt->cam, rt->cam->phi * ANG, \
				rt->cam->theta * ANG);
}
