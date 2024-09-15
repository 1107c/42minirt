/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:32:35 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/08 12:32:35 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_rt(t_rt *rt)
{
	rt->mlx_ptr = mlx_init();
	if (!rt->mlx_ptr)
		return (mlx_error(MLXERR));
	rt->width = (double) WIDTH;
	rt->height = (double) HEIGHT;
	rt->win_ptr = mlx_new_window(rt->mlx_ptr, rt->width, rt->height, TITLE);
	init_img(rt);
	win_button(rt);
	mlx_loop(rt->mlx_ptr);
}

void	init_img(t_rt *rt)
{
	rt->img.img_ptr = mlx_new_image(rt->mlx_ptr, rt->width, rt->height);
	rt->img.img_pixels_ptr = mlx_get_data_addr(rt->img.img_ptr, &rt->img.bits_per_pixel, \
					&rt->img.line_len, &rt->img.endian);
}

//t_cam	init_cam(t_rt *rt)
//{
//	t_cam	cam;



//	returm (cam);
//}
