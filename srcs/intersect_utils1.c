/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:56:28 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/21 12:56:28 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static double	get_parallel_norm_hit(t_fig *cy, t_vector point, t_vector end);
static t_vector	find_closest_center(t_fig *cy, t_vector point);

t_util	init_cy_util(t_fig *cy, t_vector p1, t_vector p2)
{
	t_util	util;

	util.origin = p1;
	util.ray_dir = sub_vec(p2, p1);
	util.from_fig_center = sub_vec(p1, cy->xyz);
	util.dn = dot_product(util.ray_dir, cy->normal_vec);
	util.abc[0] = dot_product(util.ray_dir, util.ray_dir) - util.dn * util.dn;
	util.abc[1] = dot_product(util.ray_dir, util.from_fig_center) \
				- dot_product(util.from_fig_center, cy->normal_vec) * util.dn;
	util.abc[2] = dot_product(util.from_fig_center, util.from_fig_center) \
				- dot_product(util.from_fig_center, cy->normal_vec) \
				* dot_product(util.from_fig_center, cy->normal_vec) \
				- (cy->diameter * cy->diameter) / 4;
	util.det = util.abc[1] * util.abc[1] - util.abc[0] * util.abc[2];
	return (util);
}

double	parallel_to_cy_norm(t_util util, t_fig *cy, t_vector p1, t_vector p2)
{
	if (fabs(util.abc[2]) < EPSILON)
		return (get_parallel_norm_hit(cy, p1, p2));
	return (-1.0);
}

double	get_parallel_norm_hit(t_fig *cy, t_vector point, t_vector end)
{
	t_vector	closer_area;
	t_vector	t[2];
	double		height;
	double		total_dist;

	closer_area = find_closest_center(cy, point);
	t[0] = sub_vec(closer_area, point);
	height = fabs(dot_product(t[0], cy->normal_vec));
	t[1] = sub_vec(end, point);
	total_dist = sqrt(dot_product(t[1], t[1]));
	return (height / total_dist);
}

t_vector	find_closest_center(t_fig *cy, t_vector point)
{
	t_vector	top;
	t_vector	bottom;
	t_vector	t[2];
	double		dist[2];

	bottom = cy->xyz;
	top = add_vec(cy->xyz, mul_vec(cy->normal_vec, cy->height));
	t[0] = sub_vec(bottom, point);
	t[1] = sub_vec(top, point);
	dist[0] = dot_product(t[0], t[0]);
	dist[1] = dot_product(t[1], t[1]);
	if (dist[0] < dist[1])
		return (bottom);
	return (top);
}

void	get_cy_solution(t_util *util, t_fig *cy)
{
	util->t[0] = (-util->abc[1] + sqrt(util->det)) / util->abc[0];
	util->t[1] = (-util->abc[1] - sqrt(util->det)) / util->abc[0];
	util->alpha = dot_product(util->origin, cy->normal_vec) \
				+ util->t[0] * util->dn \
				- dot_product(cy->xyz, cy->normal_vec);
	util->beta = util->alpha + (util->t[1] - util->t[0]) * util->dn;
}
