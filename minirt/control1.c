/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:35:01 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/15 18:35:01 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	win_close(t_rt *rt)
{
	mlx_destroy_image(rt->mlx_ptr, rt->img.img_ptr);
	mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	mlx_destroy_display(rt->mlx_ptr);
	free_obj(&rt->obj);
	free_light(&rt->light);
	write(1, "closed\n", 7);
	exit(0);
	return (1);
}

static int	key_input(int key, t_rt *rt)
{
	if (key == XK_Escape)
	{
		mlx_destroy_image(rt->mlx_ptr, rt->img.img_ptr);
		mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
		mlx_destroy_display(rt->mlx_ptr);
		free_obj(&rt->obj);
		free_light(&rt->light);
		write(1, "closed\n", 7);
		exit(0);
	}
	return (1);
}

void	win_button(t_rt *rt)
{
	mlx_hook(rt->win_ptr, KeyPress, KeyPressMask, key_input, rt);
	mlx_hook(rt->win_ptr, DestroyNotify, NoEventMask, win_close, rt);
}
