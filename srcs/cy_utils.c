/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:47:48 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/29 21:47:48 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	get_cy_type(t_xs *xs);

double	parallel_to_cy_norm(t_fig *cy, t_xs *xs)
{
	t_vector	closer_area;
	t_vector	center_vec;
	double		height;

	if (fabs(xs->abc[2]) >= EPSILON)
		return (-1.0);
	closer_area = find_closest_center(cy, xs->from, xs->ray_dir);
	center_vec = sub_vec(closer_area, xs->from);
	height = fabs(dot_product(center_vec, cy->normal_vec));
	return (height / xs->total_dist);
}

t_vector	find_closest_center(t_fig *cy, t_vector point, t_vector ray)
{
	t_vector	top;
	t_vector	bottom;
	t_vector	t[2];
	double		dist[2];
	double		c;

	bottom = cy->xyz;
	top = add_vec(cy->xyz, mul_vec(cy->normal_vec, cy->height));
	t[0] = sub_vec(bottom, point);
	t[1] = sub_vec(top, point);
	dist[0] = dot_product(t[0], t[0]);
	dist[1] = dot_product(t[1], t[1]);
	c = dot_product(ray, t[0]);
	if (dist[0] < dist[1])
	{
		if (c > 0)
			return (bottom);
		return (top);
	}
	c = dot_product(ray, t[1]);
	if (c > 0)
		return (top);
	return (bottom);
}

void	get_cy_solution(t_xs *xs)
{
	double	temp_t;

	xs->t[0] = (-xs->abc[1] + sqrt(xs->det)) / xs->abc[0];
	xs->t[1] = (-xs->abc[1] - sqrt(xs->det)) / xs->abc[0];
	if (xs->t[0] > xs->t[1])
	{
		temp_t = xs->t[0];
		xs->t[0] = xs->t[1];
		xs->t[1] = temp_t;
	}
	xs->alpha = xs->ecn + xs->t[0] * xs->dn;
	xs->beta = xs->alpha + (xs->t[1] - xs->t[0]) * xs->dn;
	xs->type = get_cy_type(xs);
}

int	get_cy_type(t_xs *xs)
{
	if ((xs->alpha < 0 && xs->beta < 0) \
		|| (xs->alpha > xs->h && xs->beta > xs->h) \
		|| (xs->t[0] <= EPSILON && xs->t[1] <= EPSILON))
		return (NO_HIT);
	else if ((xs->alpha < 0 || xs->alpha > xs->h) \
		&& (xs->beta > 0 && xs->beta < xs->h))
		return (CENTER_SIDE_HIT);
	else if ((xs->alpha < 0 && xs->beta > xs->h) \
		|| (xs->alpha > xs->h && xs->beta < 0))
		return (CENTER_CENTER_HIT);
	else if ((xs->alpha >= 0 && xs->alpha <= xs->h) \
		&& (xs->beta >= 0 && xs->beta <= xs->h))
		return (SIDE_SIDE_HIT);
	else if ((xs->alpha > 0 && xs->alpha < xs->h) \
		&& (xs->beta < 0 || xs->beta > xs->h))
		return (SIDE_CENTER_HIT);
	return (NO_HIT);
}

double	get_cy_up_hit(t_fig *cy, t_xs *xs)
{
	t_vector	close;
	double		height;
	double		c;
	double		hyp;

	close = find_closest_center(cy, xs->from, xs->ray_dir);
	height = fabs(dot_product(sub_vec(close, xs->from), \
			cy->normal_vec));
	c = fabs(dot_product(xs->ray_dir, cy->normal_vec)) \
			/ xs->total_dist;
	hyp = height / c;
	return (hyp / xs->total_dist);
}
