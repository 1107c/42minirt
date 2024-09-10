/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/09 15:04:08 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	draw_plane(t_rt *rt);
static void	draw_sphere(t_rt *rt);
static void	draw_cylinder(t_rt *rt);

void	draw(t_rt *rt)
{
	//t_ray	*ray;

	rt->cam->as_ratio = WINDOW_WIDTH / (2 * tan(ANG * (rt->cam->fov / 2)));
	printf("ratio: %lf\n", rt->cam->as_ratio);
	get_cam_basis(rt->cam);
	// ray = cam_ray(rt->cam);
	// cam_ray(rt->cam, rt, 0, 0);
	// cam_ray(rt->cam, rt, 1920, 0);
	// cam_ray(rt->cam, rt, 0, 1080);
	// cam_ray(rt->cam, rt, 1920, 1080);
	// draw_plane(rt);
	// draw_sphere(rt);
	draw_cylinder(rt);
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

void	draw_plane(t_rt *rt)
{
	t_vector	start_point;
	t_vector	save_point;

	start_point.x = rt->cam->coords->x + rt->cam->as_ratio * rt->cam->orient_vec->x - 960 * rt->cam->right_vec->x + 540 * rt->cam->up_vec->x;
	start_point.y = rt->cam->coords->y + rt->cam->as_ratio * rt->cam->orient_vec->y - 960 * rt->cam->right_vec->y + 540 * rt->cam->up_vec->y;
	start_point.z = rt->cam->coords->z + rt->cam->as_ratio * rt->cam->orient_vec->z - 960 * rt->cam->right_vec->z + 540 * rt->cam->up_vec->z;
	save_point.x = start_point.x;
	save_point.y = start_point.y;
	save_point.z = start_point.z;
	for (int j = 0; j < WINDOW_HEIGHT; j++)
	{
		for (int i = 0; i < WINDOW_WIDTH; i++)
		{
			if (intersect_plane(rt->fig, &start_point, rt->cam->coords))
				pixel_to_image(rt->img, i, j, 0x5E35B1);
			start_point.x += rt->cam->right_vec->x;
			start_point.y += rt->cam->right_vec->y;
			start_point.z += rt->cam->right_vec->z;
		}
		save_point.x -= rt->cam->up_vec->x;
		save_point.y -= rt->cam->up_vec->y;
		save_point.z -= rt->cam->up_vec->z;
		start_point.x = save_point.x;
		start_point.y = save_point.y;
		start_point.z = save_point.z;
	}
}

void	draw_sphere(t_rt *rt)
{
	t_vector	start_point;
	t_vector	save_point;
	//t_ray		*ray;

	start_point.x = rt->cam->coords->x + rt->cam->as_ratio * rt->cam->orient_vec->x - 960 * rt->cam->right_vec->x + 540 * rt->cam->up_vec->x;
	start_point.y = rt->cam->coords->y + rt->cam->as_ratio * rt->cam->orient_vec->y - 960 * rt->cam->right_vec->y + 540 * rt->cam->up_vec->y;
	start_point.z = rt->cam->coords->z + rt->cam->as_ratio * rt->cam->orient_vec->z - 960 * rt->cam->right_vec->z + 540 * rt->cam->up_vec->z;
	save_point.x = start_point.x;
	save_point.y = start_point.y;
	save_point.z = start_point.z;
	for (int j = 0; j < WINDOW_HEIGHT; j++)
	{
		for (int i = 0; i < WINDOW_WIDTH; i++)
		{
			// ray = cam_ray(rt->cam, rt, i, j);
			if (intersect_sphere(rt->fig->next->xyz, rt->cam->coords, &start_point, (rt->fig->next->diameter / 2)))
				pixel_to_image(rt->img, i, j, 0x0000e1);
			// if (intersect_sphere(ray, rt->fig->next))
			start_point.x += rt->cam->right_vec->x;
			start_point.y += rt->cam->right_vec->y;
			start_point.z += rt->cam->right_vec->z;
		}
		save_point.x -= rt->cam->up_vec->x;
		save_point.y -= rt->cam->up_vec->y;
		save_point.z -= rt->cam->up_vec->z;
		start_point.x = save_point.x;
		start_point.y = save_point.y;
		start_point.z = save_point.z;
	}
}

void	draw_cylinder(t_rt *rt)
{
	t_vector	start_point;
	t_vector	save_point;

	start_point.x = rt->cam->coords->x + rt->cam->as_ratio * rt->cam->orient_vec->x - 960 * rt->cam->right_vec->x + 540 * rt->cam->up_vec->x;
	start_point.y = rt->cam->coords->y + rt->cam->as_ratio * rt->cam->orient_vec->y - 960 * rt->cam->right_vec->y + 540 * rt->cam->up_vec->y;
	start_point.z = rt->cam->coords->z + rt->cam->as_ratio * rt->cam->orient_vec->z - 960 * rt->cam->right_vec->z + 540 * rt->cam->up_vec->z;
	save_point.x = start_point.x;
	save_point.y = start_point.y;
	save_point.z = start_point.z;
	for (int j = 0; j < WINDOW_HEIGHT; j++)
	{
		for (int i = 0; i < WINDOW_WIDTH; i++)
		{
			if (intersect_cylinder(rt->fig, rt->cam->coords, &start_point))
				pixel_to_image(rt->img, i, j, 0x0000e1);
			start_point.x += rt->cam->right_vec->x;
			start_point.y += rt->cam->right_vec->y;
			start_point.z += rt->cam->right_vec->z;
		}
		save_point.x -= rt->cam->up_vec->x;
		save_point.y -= rt->cam->up_vec->y;
		save_point.z -= rt->cam->up_vec->z;
		start_point.x = save_point.x;
		start_point.y = save_point.y;
		start_point.z = save_point.z;
	}
}
