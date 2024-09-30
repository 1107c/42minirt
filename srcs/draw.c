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

static int	draw_line(t_worker *wk, t_vector point);
static void	init_util(t_util *util, t_vector from, t_vector to);
static void	update_closest_figure(t_util *util, t_fig *fig, \
								t_vector to, double time);

void	draw(t_rt *rt)
{
	t_worker	workers[NUM_THREADS];

	init_workers(workers, rt);
	thread_work(workers);
	mlx_put_image_to_window(rt->mlx, rt->win, \
							rt->img->img, 0, 0);
}

void	*render_scene(void *wk)
{
	t_worker	*worker;
	t_vector	point;
	t_vector	save;
	int			i;
	int			j;

	worker = wk;
	j = worker->y_start - 1;
	point = add_vec(worker->rt->cam->screen_origin, \
			mul_vec(worker->rt->cam->up_vec, -j));
	while (++j < worker->y_end)
	{
		i = -1;
		save = point;
		while (++i < WINDOW_WIDTH)
		{
			worker->rt->map[j][i] = draw_line(worker, point);
			pixel_to_image(worker->rt->img, i, j, \
						worker->util.color.final_color);
			point = add_vec(point, worker->rt->cam->right_vec);
		}
		point = sub_vec(save, worker->rt->cam->up_vec);
	}
	return (NULL);
}

int	draw_line(t_worker *wk, t_vector to)
{
	t_fig	*fig;
	double	time;

	init_util(&wk->util, wk->rt->cam->coords, to);
	fig = wk->rt->fig;
	while (fig)
	{
		time = get_ray_dist(fig, &wk->util.xs);
		if (time > 0 && time <= wk->util.time)
			update_closest_figure(&wk->util, fig, to, time);
		fig = fig->next;
	}
	if (!wk->util.vec.fig)
		return (0);
	if (wk->util.vec.fig->is_bump == 1)
		bump(wk, &wk->util.vec, &wk->util.color);
	else
		multi_lightning(wk->rt->light, wk->rt->fig, &wk->util, \
			wk->rt->amblight);
	if (wk->util.vec.fig->is_check == 1)
		checkerboard(&wk->util.vec, &wk->util.color);
	return (wk->util.vec.fig->idx + 48);
}

void	init_xs(t_xs *xs)
{
	xs->from = init_vector(0, 0, 0);
	xs->ray_dir = init_vector(0, 0, 0);
	xs->from_fig_center = init_vector(0, 0, 0);
	xs->alpha = 0;
	xs->beta = 0;
	xs->det = 0;
	xs->dn = 0;
	xs->ecn = 0;
	xs->ecd = 0;
	xs->c = 0;
	xs->h = 0;
	xs->total_dist = 0;
	xs->left = 0;
	xs->right = 0;
	xs->type = 0;
	xs->flag = 0;
}

void	init_util(t_util *util, t_vector from, t_vector to)
{
	init_xs(&util->xs);
	util->vec.fig = NULL;
	util->vec.inter_vec = init_vector(0, 0, 0);
	util->vec.n_vec = init_vector(0, 0, 0);
	util->time = INF;
	util->xs.from = from;
	util->xs.ray_dir = sub_vec(to, from);
	util->xs.total_dist = sqrt(dot_product(util->xs.ray_dir, \
							util->xs.ray_dir));
	util->color.dif_sum = init_vector(0, 0, 0);
	util->color.spe_sum = init_vector(0, 0, 0);
	util->color.final_color = init_vector(0, 0, 0);
	util->color.l_sum = init_vector(0, 0, 0);
}

void	update_closest_cylinder(t_util *util, t_fig *fig)
{
	double	theta;

	if (util->xs.flag == 1)
		util->vec.n_vec = fig->normal_vec;
	else if (util->xs.flag == 2)
		util->vec.n_vec = invert_vec(fig->normal_vec);
	else if (util->xs.flag == 3)
		util->vec.n_vec = init_vector(0, 0, 0);
	else
	{
		util->vec.n_vec = sub_vec(util->vec.inter_vec, fig->xyz);
		theta = dot_product(util->vec.n_vec, fig->normal_vec) / \
			sqrt(dot_product(util->vec.n_vec, util->vec.n_vec));
		util->vec.n_vec = sub_vec(util->vec.n_vec, \
			mul_vec(fig->normal_vec, theta));
		util->vec.n_vec = normalize_vec(util->vec.n_vec);
	}
}

void	update_closest_figure(t_util *util, t_fig *fig, \
								t_vector to, double time)
{
	util->time = time;
	util->vec.fig = fig;
	util->vec.inter_vec = add_vec(util->xs.from, \
							mul_vec(util->xs.ray_dir, time));
	if (fig->type == PLANE)
		util->vec.n_vec = fig->normal_vec;
	else if (fig->type == SPHERE)
	{
		if (!util->xs.flag)
			util->vec.n_vec = normalize_vec(sub_vec(util->vec.inter_vec, \
				fig->xyz));
		else
			util->vec.n_vec = init_vector(0, 0, 0);
	}
	else if (fig->type == CYLINDER)
		update_closest_cylinder(util, fig);
	else
		util->vec.n_vec = get_cone_normal(fig, \
							util->xs.from, to, time);
}
