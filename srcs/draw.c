/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 23:47:18 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	draw_line(t_rt *rt, t_vector point, int i, int j);
static void	checekrboard(t_rt *rt, t_vector point, t_fig *fig, double t);
static int	is_checker(double u, double v, int checker_size);

void	draw(t_rt *rt)
{
	t_vector	point;
	int			i;
	int			j;

	i = -1;
	j = -1;
	point = init_point(rt->cam);
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
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
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
		t = get_ray_dist(point, fig, rt, &rt->vec);
		if (t >= 0 && t <= d)
		{
			d = t;
			multi_lightning(rt, &rt->vec, &rt->color, fig);
			if (rt->selected && rt->selected->idx == fig->idx && \
				rt->selected->is_check == 1)
				checekrboard(rt, point, fig, t);
			pixel_to_image(rt->img, i, j, rt->color.final_color);
			rt->map[j][i] = fig->idx + 48;
		}
		fig = fig->next;
	}
}

void	checekrboard(t_rt *rt, t_vector point, t_fig *fig, double t)
{
	double		uv[2];

	if (fig->type == SPHERE)
		get_sphere_uv(uv, fig, rt);
	else if (fig->type == PLANE)
		get_plane_uv(point, fig, &uv[0], &uv[1]);
	else if (fig->type == CYLINDER)
	{
		get_cylinder_uv(point, uv, fig, rt, t);
		uv[0] = fig->diameter / 2;
	}
	if (is_checker(uv[0], uv[1], 10))
		rt->color.final_color = (t_vector){fmin(255, rt->color.spe_sum.x), \
		fmin(255, rt->color.spe_sum.y), \
		fmin(255, rt->color.spe_sum.z), 0};
	else
		rt->color.final_color = (t_vector){fmin(255, 255 + \
		rt->color.spe_sum.x), fmin(255, 255 + \
		rt->color.spe_sum.y), \
		fmin(255, 255 + rt->color.spe_sum.z), 0};
}

int	is_checker(double u, double v, int checker_size)
{
	int	u_check;
	int	v_check;

	if (u < 0)
		u = -u + 0.1;
	if (v < 0)
		v = -v + 0.1;
	u_check = (int)(u * checker_size);
	v_check = (int)(v * checker_size);
	return ((u_check + v_check) % 2);
}
