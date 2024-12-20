/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:53:00 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/28 17:53:00 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	init_util(t_util *util, t_vector from, t_vector to);
static void	init_xs(t_xs *xs);

void	draw(t_rt *rt)
{
	t_worker	workers;

	workers.y_start = 0;
	workers.y_end = WINDOW_HEIGHT;
	workers.rt = rt;
	render_scene(&workers);
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
		if (time > 0 && time < wk->util.time - EPSILON)
			update_closest_figure(&wk->util, fig, time);
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
	xs->t_a = 0;
	xs->t_b = 0;
}
