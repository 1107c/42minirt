/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:06:34 by ksuh              #+#    #+#             */
/*   Updated: 2024/07/04 13:23:33 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_image	*init_img(void *mlx);
static t_cam	*init_cam();
static t_fig	*init_fig();
static t_light	*init_light();
static t_amblight	*init_amblight();

t_rt	*init_rt()
{
	t_rt	*rt;

	rt = malloc(sizeof(t_rt));
	rt->mlx = mlx_init();
	rt->win_x = WINDOW_WIDTH;
	rt->win_y = WINDOW_HEIGHT;
	rt->win = mlx_new_window(rt->mlx, rt->win_x, rt->win_y, WINDOW_TITLE);
	rt->img = init_img(rt->mlx);
	rt->cam = init_cam();
	rt->fig = init_fig();
	rt->light = init_light();
	rt->amblight = init_amblight();
	return (rt);
}

t_image	*init_img(void *mlx)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img->buffer = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
				&img->size_line, &img->endian);
	return (img);
}

t_cam	*init_cam()
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		return (NULL);
	// or ft_memset
	cam->x = 0;
	cam->y = 0;
	cam->z = 0;
	cam->vx = 0;
	cam->vy = 0;
	cam->vz = 0;
	cam->fov = 0;
	cam->move_x = 0;
	cam->move_y = 0;
	return (cam);
}

t_fig	*init_fig()
{
	t_fig	*fig;

	fig = malloc(sizeof(t_fig));
	if (!fig)
		return (NULL);
	fig->type = PLANE;
	fig->x = 0;
	fig->y = 0;
	fig->z = 0;
	fig->vx = 0;
	fig->vy = 0;
	fig->vz = 0;
	fig->diameter = 0;
	fig->height = 0;
	fig->r = 0;
	fig->g = 0;
	fig->b = 0;
	return (fig);
}

t_light	*init_light()
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->x = 0;
	light->y = 0;
	light->z = 0;
	light->brightness = 0;
	light->r = 0;
	light->g = 0;
	light->b = 0;
	return (light);
}

t_amblight	*init_amblight()
{
	t_amblight	*amblight;

	amblight = malloc(sizeof(t_amblight));
	if (!amblight)
		return (NULL);
	amblight->light_ratio = 0;
	amblight->r = 0;
	amblight->g = 0;
	amblight->b = 0;
	return (amblight);
}
