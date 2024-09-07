/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 14:27:56 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	draw_plane(t_rt *rt);

void	draw(t_rt *rt)
{
	(void)rt;

	//draw_plane(rt);
	draw_sphere(rt);
	// draw_cylinder();
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
}

// ∗ identifier: pl
// ∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// ∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
// ∗ R,G,B colors in range [0-255]: 0,0,225

void	pixel_to_image(t_image *img, double x, double y, int color)
{
	int	pixel;

	pixel = ((int)y * img->size_line) + ((int)x * 4);
	img->buffer[pixel + 0] = (color) & 0xff;
	img->buffer[pixel + 1] = (color >> 8) & 0xff;
	img->buffer[pixel + 2] = (color >> 16) & 0xff;
	img->buffer[pixel + 3] = (color >> 24);
}

void	draw_plane(t_rt *rt)
{
	for (int i = 0; i < WINDOW_WIDTH; i++)
	{
		for (int j = 0; j < WINDOW_HEIGHT; j++)
			pixel_to_image(rt->img, i, j, 0x0000e1);
	}
}

void	draw_sphere(t_rt *rt)
{
	int	x;
	int	y;
	t_ray	*tray;
	float	f;

	for (x = 0; x < rt->win_y; x++)
	{
		for (y = 0; y < rt->win_x; y++)
		{
			tray = cam_ray(rt->cam, rt, x, y);
			if (intersect_sphere(tray, rt->fig))
				pixel_to_image(rt->img, y, x, 0x0000e1);
			else
				pixel_to_image(rt->img, y, x, 0x000000);
		}
	}
}
