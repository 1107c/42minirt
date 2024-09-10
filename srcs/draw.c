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


void	draw(t_rt *rt)
{
	//t_ray	*ray;
	t_fig		*tmp;

	tmp = rt->fig;

	rt->cam->distance_to_view = WINDOW_WIDTH / (2 * tan(ANG * (rt->cam->fov / 2)));
	printf("ratio: %lf\n", rt->cam->distance_to_view);
	get_cam_basis(rt->cam);
	// ray = cam_ray(rt->cam);
	// cam_ray(rt->cam, rt, 0, 0);
	// cam_ray(rt->cam, rt, 1920, 0);
	// cam_ray(rt->cam, rt, 0, 1080);
	// cam_ray(rt->cam, rt, 1920, 1080);
	// draw_plane(rt);
	while (tmp->next)
	{
		draw_fig(rt, tmp, -1, -1);
		tmp = tmp->next;
	}
	// draw_cylinder();
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

// void	draw_plane(t_rt *rt)
// {
// 	t_vector	start_point;
// 	t_vector	save_point;
// 	//t_vector	line;

// 	start_point.x = rt->cam->coords->x + rt->cam->distance_to_view * rt->cam->orient_vec->x - 960 * rt->cam->right_vec->x + 540 * rt->cam->up_vec->x;
// 	start_point.y = rt->cam->coords->y + rt->cam->distance_to_view * rt->cam->orient_vec->y - 960 * rt->cam->right_vec->y + 540 * rt->cam->up_vec->y;
// 	start_point.z = rt->cam->coords->z + rt->cam->distance_to_view * rt->cam->orient_vec->z - 960 * rt->cam->right_vec->z + 540 * rt->cam->up_vec->z;
// 	save_point.x = start_point.x;
// 	save_point.y = start_point.y;
// 	save_point.z = start_point.z;
// 	for (int j = 0; j < WINDOW_HEIGHT; j++)
// 	{
// 		for (int i = 0; i < WINDOW_WIDTH; i++)
// 		{
// 			// line.x = start_point.x - rt->cam->coords->x;
// 			// line.y = start_point.y - rt->cam->coords->y;
// 			// line.z = start_point.z - rt->cam->coords->z;
// 			if (intersect_plane(rt->fig, &start_point, rt->cam->coords))
// 				pixel_to_image(rt->img, i, j, 0x5E35B1);
// 			start_point.x += rt->cam->right_vec->x;
// 			start_point.y += rt->cam->right_vec->y;
// 			start_point.z += rt->cam->right_vec->z;
// 		}
// 		save_point.x -= rt->cam->up_vec->x;
// 		save_point.y -= rt->cam->up_vec->y;
// 		save_point.z -= rt->cam->up_vec->z;
// 		start_point.x = save_point.x;
// 		start_point.y = save_point.y;
// 		start_point.z = save_point.z;
// 	}
// }

void	draw_fig(t_rt *rt, t_fig *tmp, int i, int j)
{
	t_vector	start_point;

	start_point = (t_vector){rt->cam->coords->x + rt->cam->distance_to_view * rt->cam->orient_vec->x - 960 * rt->cam->right_vec->x + 540 * rt->cam->up_vec->x,
		rt->cam->coords->y + rt->cam->distance_to_view * rt->cam->orient_vec->y - 960 * rt->cam->right_vec->y + 540 * rt->cam->up_vec->y,
		rt->cam->coords->z + rt->cam->distance_to_view * rt->cam->orient_vec->z - 960 * rt->cam->right_vec->z + 540 * rt->cam->up_vec->z, NULL};
	while (++j < WINDOW_HEIGHT)
	{
		while (++i < WINDOW_WIDTH)
		{
			if (intersect_plane(tmp, &start_point, rt->cam->coords) && tmp->type == 0)
				pixel_to_image(rt->img, i, j, encode_rgb(tmp->rgb->x, tmp->rgb->y, tmp->rgb->z));
			if (intersect_sphere(tmp->xyz, rt->cam->coords, &start_point, tmp->diameter / 2) && tmp->type == 1)
				pixel_to_image(rt->img, i, j, encode_rgb(tmp->rgb->x, tmp->rgb->y, tmp->rgb->z));
			start_point.x += rt->cam->right_vec->x;
			start_point.y += rt->cam->right_vec->y;
			start_point.z += rt->cam->right_vec->z;
		}
		start_point.x -= rt->cam->up_vec->x + rt->cam->right_vec->x * i;
		start_point.y -= rt->cam->up_vec->y + rt->cam->right_vec->y * i;
		start_point.z -= rt->cam->up_vec->z + rt->cam->right_vec->z * i;
		i = -1;
	}
}
