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
static void	checkerboard(t_rt *rt, t_vector point,  t_vec *vec, t_color *color);
static int	is_checker(double u, double v, int checker_size);

void	draw(t_rt *rt)
{
	t_worker	workers[THREADS_NUM];

	init_workers(workers, rt);
	thread_work(workers);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
}

void	*render_scene(void *wk)
{
	t_worker	*worker;
	t_vector	point;
	t_vector	p1;
	int			i;
	int			j;
	time_t			start;
	time_t			end;

	start = clock();
	worker = wk;
	j = worker->y_start;
	point = add_vec(worker->rt->cam->screen_origin, \
			mul_vec(worker->rt->cam->up_vec, -j));
	while (j < worker->y_end)
	{
		i = 0;
		p1 = point;
		while (i < WINDOW_WIDTH)
		{
			draw_line(worker->rt, point, i, j);
			point = add_vec(point, mul_vec(worker->rt->cam->right_vec, 1));
			i += 1;
		}
		j += 1;
		point = sub_vec(p1, mul_vec(worker->rt->cam->up_vec, 1));
	}
	end = clock();
	// printf("time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	return (NULL);
}


void    bump(t_rt *rt, t_vector point, t_vec *vec, t_color *color)
{
	double  uv[2];
    t_vector normal_from_map;
    t_vector color_from_map;
    t_vector tangent, bitangent;
    t_vector new_normal;

    if (vec->fig->type == SPHERE)
        get_sphere_uv(uv, vec->n_vec, rt);
    else if (vec->fig->type == PLANE)
        get_plane_uv(vec->inter_vec, vec->fig, &uv[0], &uv[1]);
    else if (vec->fig->type == CYLINDER || vec->fig->type == CONE)
        get_cylinder_uv(vec->inter_vec, uv, vec->fig);
    if (vec->fig->bump->normal_width > vec->fig->bump->normal_height)
    	vec->fig->bump->normal_width = vec->fig->bump->normal_height;
    else
     	vec->fig->bump->normal_height = vec->fig->bump->normal_width;
    int u = (uv[0] * (vec->fig->bump->normal_width - 1));
    int v = (uv[1] * (vec->fig->bump->normal_height - 1));
   	if (u < 0)
    	{
	     	while (u < vec->fig->bump->normal_width)
				u += vec->fig->bump->normal_width;
					if (u < vec->fig->bump->normal_height / 10000)
						u += vec->fig->bump->normal_width* 0.9999 ;
					else if (u > vec->fig->bump->normal_width - vec->fig->bump->normal_width / 10000)
						u -= vec->fig->bump->normal_width* 0.9999 ;
     	}
		else if (u >= vec->fig->bump->normal_width)
		{
			while (u >= vec->fig->bump->normal_width)
				u -= vec->fig->bump->normal_width;

		}
   	if (v < 0)
    	{
	     	while (v < 0)
				v += vec->fig->bump->normal_height;
				if (v < vec->fig->bump->normal_height / 10000)
					v += vec->fig->bump->normal_height* 0.9999 ;
					else if (v > vec->fig->bump->normal_height - vec->fig->bump->normal_height / 10000)
						v -= vec->fig->bump->normal_height* 0.9999 ;
     	}
		else if (v >= vec->fig->bump->normal_height)
		{
			while (v >= vec->fig->bump->normal_height)
					v -= vec->fig->bump->normal_height;

		}
	    normal_from_map = vec->fig->bump->normal_map[v][u];
		color_from_map = vec->fig->bump->color_map[v][u];

	    t_vector	y_unit_vector;
	    if (fabs(vec->n_vec.y) != 1)
			y_unit_vector = (t_vector){0, 1, 0, 0};
		else
			y_unit_vector = (t_vector){0, 0, -vec->n_vec.y, 0};
		tangent = normalize_vec(cross_product(y_unit_vector, vec->n_vec));
		bitangent = normalize_vec(cross_product( vec->n_vec , tangent));
	    new_normal.x = tangent.x * normal_from_map.x + bitangent.x * normal_from_map.y + vec->n_vec.x * normal_from_map.z;
	    new_normal.y = tangent.y * normal_from_map.x + bitangent.y * normal_from_map.y + vec->n_vec.y * normal_from_map.z;
	    new_normal.z = tangent.z * normal_from_map.x + bitangent.z * normal_from_map.y + vec->n_vec.z * normal_from_map.z;
	    new_normal = normalize_vec(new_normal);

	    vec->n_vec = new_normal;

	    multi_lightning(rt, vec, color, vec->fig);
	    color->final_color = color_from_map;
}


void	draw_line(t_rt *rt, t_vector point, int i, int j)
{
	t_fig	*fig;
	t_vec	vec;
	t_color	color;
	double	d;
	double	t;

	fig = rt->fig;
	d = INF;
	vec.fig = NULL;
	color.final_color = (t_vector) {0, 0, 0, 0};
	vec.inter_vec = (t_vector) {0, 0, 0, 0};
	vec.n_vec = (t_vector) {0, 0, 0, 0};
	while (fig)
	{
		t = get_ray_dist(point, fig, rt, &vec);
		if (t > 0 && t <= d)
		{
			d = t;
			vec.inter_tg_vec = vec.inter_vec;
			vec.n_tg_vec = vec.n_vec;
			vec.fig = fig;
		}
		fig = fig->next;
	}
	vec.inter_vec = vec.inter_tg_vec;
	vec.n_vec = vec.n_tg_vec;
	if (!vec.fig)
	{
		rt->map[j][i] = 0;
		pixel_to_image(rt->img, i, j, color.final_color);
		return;
	}
	rt->map[j][i] = vec.fig->idx + 48;
	if (vec.fig->is_bump == 1)
		bump(rt, point, &vec, &color);
	else
		multi_lightning(rt, &vec, &color, vec.fig);
	if (vec.fig->is_check == 1)
		checkerboard(rt, point, &vec, &color);
	pixel_to_image(rt->img, i, j, color.final_color);
}

void	checkerboard(t_rt *rt, t_vector point,  t_vec *vec, t_color *color)
{
	double	uv[2];

	if (vec->fig->type == SPHERE)
		get_sphere_uv(uv, vec->n_vec, rt);
	else if (vec->fig->type == PLANE)
		get_plane_uv(vec->inter_vec, vec->fig, &uv[0], &uv[1]);
	else if (vec->fig->type == CYLINDER || vec->fig->type == CONE)
		get_cylinder_uv(vec->inter_vec, uv, vec->fig);
	if (is_checker(uv[0], uv[1], 10))
		color->final_color = (t_vector){fmin(255, color->spe_sum.x), \
		fmin(255, color->spe_sum.y), \
		fmin(255, color->spe_sum.z), 0};
	else
		color->final_color = (t_vector){fmin(255, 255 + \
			color->spe_sum.x), fmin(255, 255 + \
				color->spe_sum.y), \
			fmin(255, 255 + color->spe_sum.z), 0};
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
