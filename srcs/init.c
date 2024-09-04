/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:06:34 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 14:31:57 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_image		*init_img(void *mlx);
static t_cam		*init_cam();
static t_fig		*init_fig();
static t_light		*init_light();
static t_amblight	*init_amblight();
static t_vector		*init_vector();

t_rt	*init_rt()
{
	t_rt	*rt;

	rt = malloc(sizeof(t_rt));
	if (!rt)
		return (NULL);
	rt->mlx = mlx_init();
	if (!rt->mlx)
		return (NULL);
	mlx_get_screen_size(rt->mlx, &rt->win_x, &rt->win_y);
	rt->win = mlx_new_window(rt->mlx, rt->win_x, rt->win_y, WINDOW_TITLE);
	if (!rt->win)
		return (NULL);
	rt->img = init_img(rt->mlx);
	rt->cam = init_cam();
	rt->fig = init_fig();
	rt->light = init_light();
	rt->amblight = init_amblight();
	rt->error = NULL;
	if (!rt->img || !rt->cam || !rt->fig || !rt->light || !rt->amblight)
		return (NULL);
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
	cam->xyz = init_vector();
	cam->orient_vec = init_vector();
	if (!cam->xyz || !cam->orient_vec)
		return (free(cam->xyz), free(cam->orient_vec), NULL);
	cam->fov = 0;
	cam->move_x = 0;
	cam->move_y = 0;
	cam->ch = 0;
	return (cam);
}

t_fig	*init_fig()
{
	t_fig	*fig;

	fig = malloc(sizeof(t_fig));
	if (!fig)
		return (NULL);
	fig->type = PLANE;
	fig->xyz = init_vector();
	fig->normal_vec = init_vector();
	fig->rgb = init_vector();
	if (!fig->xyz || !fig->normal_vec || !fig->rgb)
		return (free(fig->xyz), free(fig->normal_vec), free(fig->rgb), NULL);
	fig->diameter = 0;
	fig->height = 0;
	fig->next = NULL;
	return (fig);
}

t_light	*init_light()
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->xyz = init_vector();
	light->rgb = init_vector();
	if (!light->xyz || !light->rgb)
		return (free(light->xyz), free(light->rgb), free(light), NULL);
	light->brightness = 0;
	light->ch = 0;
	light->next = NULL;
	return (light);
}

t_amblight	*init_amblight()
{
	t_amblight	*amblight;

	amblight = malloc(sizeof(t_amblight));
	if (!amblight)
		return (NULL);
	amblight->light_ratio = 0;
	amblight->rgb = init_vector();
	if (!amblight->rgb)
		return (free(amblight), NULL);
	amblight->ch = 0;
	return (amblight);
}

t_vector		*init_vector()
{
	t_vector	*vec;

	vec = malloc(sizeof(t_vector));
	if (!vec)
		return (NULL);
	vec->x = 0;
	vec->y = 0;
	vec->z = 0;
	vec->error = NULL;
	return (vec);
}
