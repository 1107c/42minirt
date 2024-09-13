/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/10 18:39:47 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	clear_image(t_image *img);

void	draw(t_rt *rt)
{
	t_fig	*fig;

	fig = rt->fig;
	rt->cam->distance_to_view = WINDOW_WIDTH / \
								(2 * tan(ANG * (rt->cam->fov / 2)));
	update_basis(rt->cam);
	// printf("ratio: %lf\n", rt->cam->distance_to_view);
	clear_image(rt->img);
	while (fig)
	{
		draw_fig(rt, fig, -1, -1);
		fig = fig->next;
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
}

void	pixel_to_image(t_image *img, double x, double y, int color)
{
	int	pixel;

	pixel = ((int)y * img->size_line) + ((int)x * 4);
	img->buffer[pixel + 0] = (color) & 0xff;
	img->buffer[pixel + 1] = (color >> 8) & 0xff;
	img->buffer[pixel + 2] = (color >> 16) & 0xff;
	img->buffer[pixel + 3] = (color >> 24);
}

int	encode_rgb(double red, double green, double blue)
{
	return ((int)red << 16 | (int)green << 8 | (int)blue);
}

void	draw_fig(t_rt *rt, t_fig *tmp, int i, int j)
{
	t_vector	start_point;

	start_point = (t_vector){rt->cam->coords.x + rt->cam->distance_to_view * rt->cam->orient_vec.x - 960 * rt->cam->right_vec.x + 540 * rt->cam->up_vec.x,
		rt->cam->coords.y + rt->cam->distance_to_view * rt->cam->orient_vec.y - 960 * rt->cam->right_vec.y + 540 * rt->cam->up_vec.y,
		rt->cam->coords.z + rt->cam->distance_to_view * rt->cam->orient_vec.z - 960 * rt->cam->right_vec.z + 540 * rt->cam->up_vec.z, NULL};
	while (++j < WINDOW_HEIGHT)
	{
		while (++i < WINDOW_WIDTH)
		{
			if (tmp->type == 0 && intersect_plane(tmp, start_point, rt->cam->coords) != -1)
				pixel_to_image(rt->img, i, j, encode_rgb(tmp->rgb.x, tmp->rgb.y, tmp->rgb.z));
			if (tmp->type == 1 && intersect_sphere(tmp->xyz, rt->cam->coords, start_point, tmp->diameter / 2) != -1)
				pixel_to_image(rt->img, i, j, encode_rgb(tmp->rgb.x, tmp->rgb.y, tmp->rgb.z));
			if (tmp->type == 2 && intersect_cylinder(tmp, rt->cam->coords, start_point) != -1)
				pixel_to_image(rt->img, i, j, encode_rgb(tmp->rgb.x, tmp->rgb.y, tmp->rgb.z));
			start_point = add_vec(start_point, rt->cam->right_vec);
		}
		start_point = sub_vec(start_point, add_vec(mul_vec(rt->cam->right_vec, i), \
		rt->cam->up_vec));
		i = -1;
	}
}

void	clear_image(t_image *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_to_image(img, x, y, 0);
			x++;
		}
		y++;
	}
}
