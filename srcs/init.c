/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:06:34 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/16 06:46:50 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_image		*init_img(void *mlx);
static t_amblight	*init_amblight(t_rt *rt);
static t_cam		*init_cam(t_rt *rt);
static int			rt_mlx_init(t_rt *rt);

t_rt	*init_rt(int fd)
{
	t_rt	*rt;

	rt = malloc(sizeof(t_rt));
	if (!rt)
		return (NULL);
	if (!rt_mlx_init(rt))
		return (free(rt), NULL);
	rt->amblight = init_amblight(rt);
	rt->cam = init_cam(rt);
	if (!rt->amblight || !rt->cam)
		return (free(rt), NULL);
	rt->fig = NULL;
	rt->light = NULL;
	rt->selected = NULL;
	rt->selected_light = NULL;
	rt->bump = NULL;
	rt->line = NULL;
	rt->error = NULL;
	rt->file_fd = fd;
	rt->light_cnt = 0;
	rt->fig_cnt = 0;
	rt->bump_cnt = 0;
	rt->did_get_normal_map = 0;
	init_map(rt);
	return (rt);
}

int	rt_mlx_init(t_rt *rt)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
		return (0);
	rt->win = mlx_new_window(rt->mlx, WINDOW_WIDTH, \
				WINDOW_HEIGHT, WINDOW_TITLE);
	if (!rt->win)
	{
		mlx_destroy_display(rt->mlx);
		return (free(rt->mlx), 0);
	}
	rt->img = init_img(rt->mlx);
	if (!rt->img)
	{
		mlx_destroy_display(rt->mlx);
		mlx_destroy_window(rt->mlx, rt->win);
		return (free(rt->mlx), 0);
	}
	return (1);
}

t_image	*init_img(void *mlx)
{
	t_image	*img;

	img = malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img->img)
		return (free(img), NULL);
	img->buffer = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
				&img->size_line, &img->endian);
	if (!img->buffer)
		return (mlx_destroy_image(mlx, img->img), free(img), NULL);
	return (img);
}

t_amblight	*init_amblight(t_rt *rt)
{
	t_amblight	*amblight;

	amblight = malloc(sizeof(t_amblight));
	if (!amblight)
		return (close_mlx(rt), NULL);
	amblight->light_ratio = 0;
	amblight->cnt = 0;
	return (amblight);
}

// comment -> yeojukim
// : 수정된 구조체에 따라 수정했습니다.
t_cam	*init_cam(t_rt *rt)
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		return (free(rt->amblight), \
				close_mlx(rt), NULL);
	cam->fov = 0;
	cam->as_ratio = 0;
	cam->distance_to_view = 0;
	cam->theta = 0;
	cam->phi = 0;
	cam->cnt = 0;
	cam->coords = init_vector(0, 0, 0);
	cam->orient_vec = init_vector(0, 0, 0);
	cam->right_vec = init_vector(0, 0, 0);
	cam->up_vec = init_vector(0, 0, 0);
	cam->origin_orient_vec = init_vector(0, 0, 0);
	cam->origin_right_vec = init_vector(0, 0, 0);
	cam->origin_up_vec = init_vector(0, 0, 0);
	cam->screen_origin = init_vector(0, 0, 0);
	return (cam);
}
