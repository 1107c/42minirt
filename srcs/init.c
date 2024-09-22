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
static t_amblight	*init_amblight(void);
static t_cam		*init_cam(void);
static int			rt_mlx_init(t_rt *rt);

t_rt	*init_rt(int fd)
{
	t_rt	*rt;

	rt = malloc(sizeof(t_rt));
	if (!rt)
		return (NULL);
	if (!rt_mlx_init(rt))
		return (NULL);
	rt->amblight = init_amblight();
	rt->cam = init_cam();
	if (!rt->amblight || !rt->cam)
		return (close_mlx(rt), free(rt->amblight), free(rt->cam), \
				free(rt), NULL);
	rt->fig = NULL;
	rt->light = NULL;
	rt->error = NULL;
	rt->line = NULL;
	rt->file_fd = fd;
	rt->light_cnt = 0;
	rt->fig_cnt = 0;
	rt->selected = NULL;
	rt->selected_light = NULL;
	init_map(rt);
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

t_amblight	*init_amblight(void)
{
	t_amblight	*amblight;

	amblight = malloc(sizeof(t_amblight));
	if (!amblight)
		return (NULL);
	amblight->light_ratio = 0;
	amblight->ch = 0;
	return (amblight);
}

// comment -> yeojukim
// : 수정된 구조체에 따라 수정했습니다.
t_cam	*init_cam(void)
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		return (NULL);
	cam->fov = 0;
	cam->vp_h = 0;
	cam->vp_w = 0;
	cam->as_ratio = 0;
	cam->distance_to_view = 0;
	cam->theta = 0;
	cam->phi = 0;
	cam->ch = 0;
	cam->coords = (t_vector){0, 0, 0, NULL};
	cam->orient_vec = (t_vector){0, 0, 0, NULL};
	cam->right_vec = (t_vector){0, 0, 0, NULL};
	cam->up_vec = (t_vector){0, 0, 0, NULL};
	cam->corner_vec = (t_vector){0, 0, 0, NULL};
	cam->origin_orient_vec = (t_vector){0, 0, 0, NULL};
	cam->origin_right_vec = (t_vector){0, 0, 0, NULL};
	cam->origin_up_vec = (t_vector){0, 0, 0, NULL};
	cam->screen_origin = (t_vector){0, 0, 0, NULL};
	cam->screen_width = (t_vector){0, 0, 0, NULL};
	return (cam);
}

int	rt_mlx_init(t_rt *rt)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
		return (0);
	mlx_get_screen_size(rt->mlx, &rt->win_x, &rt->win_y);
	rt->win = mlx_new_window(rt->mlx, rt->win_x, rt->win_y, WINDOW_TITLE);
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
