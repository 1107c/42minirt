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
	rt->cam->distance_to_view = WINDOW_WIDTH / \
								(2 * tan(ANG * (rt->cam->fov / 2)));
	update_basis(rt->cam);
	clear_image(rt->img);
	draw_fig(rt, -1, -1);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
}

void	pixel_to_image(t_image *img, double x, double y, t_vector rgb)
{
	int	pixel;
	int	color;

	color = encode_rgb(rgb.x, rgb.y, rgb.z);
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

void	draw_line(t_rt *rt, t_vector point, int i, int j)
{
	t_fig	*fig;
	double	d;
	double	t;

	fig = rt->fig;
	d = INF;
	while (fig)
	{
		if (fig->type == 0)
			t = intersect_plane(fig, rt->cam->coords, point);
		else if (fig->type == 1)
			t = intersect_sphere(fig, rt->cam->coords, point);
		else if (fig->type == 2)
			t = intersect_cylinder(fig, rt->cam->coords, point);
		if (t >= 0 && t < d)
		{
			d = t;
			pixel_to_image(rt->img, i, j, fig->rgb);
		}
		fig = fig->next;
	}
}

void	draw_fig(t_rt *rt, int i, int j)
{
	t_vector	point;

	point = (t_vector){rt->cam->coords.x + rt->cam->distance_to_view * rt->cam->orient_vec.x - 960 * rt->cam->right_vec.x + 540 * rt->cam->up_vec.x,
		rt->cam->coords.y + rt->cam->distance_to_view * rt->cam->orient_vec.y - 960 * rt->cam->right_vec.y + 540 * rt->cam->up_vec.y,
		rt->cam->coords.z + rt->cam->distance_to_view * rt->cam->orient_vec.z - 960 * rt->cam->right_vec.z + 540 * rt->cam->up_vec.z, NULL};
	while (++j < WINDOW_HEIGHT)
	{
		while (++i < WINDOW_WIDTH)
		{
			draw_line(rt, point, i, j);
			point = add_vec(point, rt->cam->right_vec);
		}
		point = sub_vec(point, add_vec(mul_vec(rt->cam->right_vec, i), \
		rt->cam->up_vec));
		i = -1;
	}
}

void	clear_image(t_image *img)
{
	t_vector	vec;
	int			x;
	int			y;

	vec = (t_vector){0, 0, 0, 0};
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_to_image(img, x, y, vec);
			x++;
		}
		y++;
	}
}
