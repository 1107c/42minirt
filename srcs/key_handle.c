/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:12:55 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/09 14:49:50 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	key_translate(int keycode, t_rt *rt);
static void	key_rotate(int keycode, t_rt *rt);

int	key_handle(int keycode, t_rt *rt)
{
	// printf("keycode: %d\n", keycode);
	if (keycode == KEY_ESC)
		close_all(rt, NULL);
	else if (keycode == KEY_UP || keycode == KEY_DOWN || \
			keycode == KEY_LEFT || keycode == KEY_RIGHT)
		key_rotate(keycode, rt);
	else if (keycode == KEY_W || keycode == KEY_A || \
		keycode == KEY_S || keycode == KEY_D || \
		keycode == KEY_Q || keycode == KEY_E)
		key_translate(keycode, rt);
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
		rt->cam->coords = add_vec(rt->cam->coords, mul_vec(rt->cam->orient_vec, 3));
	else if (keycode == KEY_S)
		rt->cam->coords = sub_vec(rt->cam->coords, mul_vec(rt->cam->orient_vec, 3));
	else if (keycode == KEY_D)
		rt->cam->coords = add_vec(rt->cam->coords, mul_vec(rt->cam->right_vec, 3));
	else if (keycode == KEY_A)
		rt->cam->coords = sub_vec(rt->cam->coords, mul_vec(rt->cam->right_vec, 3));
	else if (keycode == KEY_Q)
		rt->cam->coords = add_vec(rt->cam->coords, mul_vec(rt->cam->up_vec, 3));
	else if (keycode == KEY_E)
		rt->cam->coords = sub_vec(rt->cam->coords, mul_vec(rt->cam->up_vec, 3));
}

void	key_rotate(int keycode, t_rt *rt)
{
	if (keycode == KEY_UP)
		rt->cam->phi += 10;
	else if (keycode == KEY_DOWN)
		rt->cam->phi -= 10;
	else if (keycode == KEY_RIGHT)
		rt->cam->theta += 10;
	else if (keycode == KEY_LEFT)
		rt->cam->theta -= 10;
	get_cam_basis(rt->cam);
}
