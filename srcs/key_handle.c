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

int	key_handle(int keycode, t_rt *rt)
{
	// printf("keycode: %d\n", keycode);
	if (keycode == KEY_ESC)
		close_all(rt, NULL);
	/*else if (keycode == KEY_R)
		rt_reset(rt);
	else if (keycode == KEY_UP || keycode == KEY_DOWN || \
				keycode == KEY_LEFT || keycode == KEY_RIGHT)
		key_translate(keycode, rt);
	else if (keycode == KEY_Q || keycode == KEY_W || keycode == KEY_E || \
				keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
		key_rotate(keycode, rt);
	else if (keycode == KEY_Z || keycode == KEY_X || \
				keycode == KEY_PLUS || keycode == KEY_MINUS)
		key_scale(keycode, rt);
	else if (keycode == KEY_I || keycode == KEY_P)
		key_project(keycode, rt);
	draw(rt);*/
	return (0);
}
