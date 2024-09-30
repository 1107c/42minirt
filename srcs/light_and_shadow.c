/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  light_and_shadow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 23:47:18 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	get_final_color(t_color *c);

int	is_in_shadow(t_fig *fig, t_light *light, t_xs *xs, t_vec *vec)
{
	t_vector	l_vec;
	t_fig		*_fig;
	double		time;

	l_vec = vec->l_vec;
	xs->from = add_vec(vec->inter_vec, mul_vec(l_vec, V_EPSILON));
	xs->ray_dir = sub_vec(light->xyz, xs->from);
	xs->total_dist = sqrt(dot_product(xs->ray_dir, \
							xs->ray_dir));
	_fig = fig;
	while (_fig)
	{
		time = get_ray_dist(_fig, xs);
		if (time > 0 && time < 1)
			return (1);
		_fig = _fig->next;
	}
	return (0);
}

void	multi_lightning(t_light *light, t_fig *fig, \
	t_util *util, t_amblight *amb)
{
	t_light	*lt;

	lt = light;
	util->color.amb = mul_vec(util->vec.fig->rgb, \
	amb->light_ratio * AMBIENT_STRENGTH);
	util->vec.e_vec = normalize_vec(sub_vec(util->xs.from, \
	util->vec.inter_vec));
	while (lt)
	{
		util->vec.l_vec = normalize_vec(sub_vec(lt->xyz, util->vec.inter_vec));
		util->vec.r_vec = normalize_vec(sub_vec(mul_vec(util->vec.n_vec, 2 * \
			dot_product(util->vec.n_vec, util->vec.l_vec)), util->vec.l_vec));
		if (!is_in_shadow(fig, lt, &util->xs, &util->vec))
			add_color(&util->color, util->vec.fig, &util->vec, lt);
		lt = lt->next;
	}
	get_final_color(&util->color);
}

void	get_final_color(t_color *c)
{
	t_vector	sum;

	sum = add_vec(c->amb, add_vec(c->dif_sum, c->spe_sum));
	c->final_color.x = fmin(255, fmax(0, sum.x + c->l_sum.x));
	c->final_color.y = fmin(255, fmax(0, sum.y + c->l_sum.y));
	c->final_color.z = fmin(255, fmax(0, sum.z + c->l_sum.z));
}
