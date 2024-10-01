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
static void	fig_resize_dia(int keycode, t_rt *rt);
static void	fig_resize_height(int keycode, t_rt *rt);

int	key_handle(int keycode, t_rt *rt)
{
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
		key_checkboard_bump(keycode, rt);
	return (draw(rt), 0);
}

void	cam_translate(int keycode, t_rt *rt)
{
	if (keycode == KEY_W)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->orient_vec, CAM_MOVE));
	else if (keycode == KEY_S)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->orient_vec, -CAM_MOVE));
	else if (keycode == KEY_D)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->right_vec, CAM_MOVE));
	else if (keycode == KEY_A)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->right_vec, -CAM_MOVE));
	else if (keycode == KEY_Q)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->up_vec, CAM_MOVE));
	else if (keycode == KEY_E)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->up_vec, -CAM_MOVE));
	rt->cam->screen_origin = init_point(rt->cam);
}

void	cam_rotate(int keycode, t_rt *rt)
{
	if (keycode == KEY_UP)
		rt->cam->phi += CAM_ROT;
	else if (keycode == KEY_DOWN)
		rt->cam->phi -= CAM_ROT;
	else if (keycode == KEY_LEFT)
		rt->cam->theta -= CAM_ROT;
	else if (keycode == KEY_RIGHT)
		rt->cam->theta += CAM_ROT;
	if (rt->cam->theta >= PI_ANG)
		rt->cam->theta -= 2 * PI_ANG;
	else if (rt->cam->theta <= -PI_ANG)
		rt->cam->theta += 2 * PI_ANG;
	if (rt->cam->phi >= PI_ANG)
		rt->cam->phi -= 2 * PI_ANG;
	else if (rt->cam->phi <= -PI_ANG)
		rt->cam->phi += 2 * PI_ANG;
	update_basis(rt->cam, rt->cam->phi * ANG, \
				rt->cam->theta * ANG);
}

void	fig_resize_dia(int keycode, t_rt *rt)
{
	if (!rt->selected || rt->selected->type == PLANE)
		return ;
	if (keycode == NUM_PLUS)
		rt->selected->diameter += 2;
	else if (keycode == NUM_MINUS && rt->selected->diameter > 3)
		rt->selected->diameter -= 2;
	rt->selected->radius_sq = pow(rt->selected->diameter / 2, 2);
}

void	fig_resize_height(int keycode, t_rt *rt)
{
	if (!rt->selected || rt->selected-> type == PLANE \
		|| rt->selected->type == SPHERE)
		return ;
	if (keycode == KEY_PLUS)
		rt->selected->height += 2;
	else if (keycode == KEY_MINUS && rt->selected->height > 3)
		rt->selected->height -= 2;
}
