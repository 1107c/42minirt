/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:01:35 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/21 13:01:35 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_util		init_cn_util(t_fig *cn, t_vector p1, t_vector p2)
{
	t_util		util;
	t_vector	apex;
	t_vector	d;
	double		radius;
	double		height_ratio;
	double		h;

	util.origin = p1;
	util.ray_dir = sub_vec(p2, p1);
	// d = sub_vec(util.ray_dir, cn->normal_vec);
	// radius = cn->diameter / 2;
	// apex = add_vec(cn->xyz, mul_vec(cn->normal_vec, cn->height));
	// h = cn->height;
	// util.abc[0] = d.x * d.x + d.y * d.y - (radius * radius) / (h * h) * d.z * d.z;
	// util.abc[1] = d.x * (util.origin.x - apex.x) + d.y * (util.origin.y - apex.y) -
	// 			(radius * radius) / (h * h) * d.z * (util.origin.z - apex.z);
	// util.abc[2] = (util.origin.x - apex.x) * (util.origin.x - apex.x) +
	// 			(util.origin.y - apex.y) * (util.origin.y - apex.y) -
	// 			(radius * radius) / (h * h) * (util.origin.z - apex.z) * (util.origin.z - apex.z);
	util.from_fig_center = sub_vec(p1, cn->xyz);
	util.dn = dot_product(util.ray_dir, cn->normal_vec);
	util.ecn = dot_product(cn->normal_vec, util.from_fig_center);
	util.ecd = dot_product(util.ray_dir, util.from_fig_center);
	radius = cn->diameter / 2;
	height_ratio = pow(radius / cn->height, 2);
	util.abc[0] = dot_product(util.ray_dir, util.ray_dir) - \
				(1 + height_ratio) \
				* pow(util.dn, 2);
	util.abc[1] = util.ecd + util.dn * ((pow(radius, 2) / cn->height) \
			- (1 + height_ratio) * util.ecn);
	util.abc[2] = dot_product(util.from_fig_center, util.from_fig_center) \
			+ 2 * (pow(radius, 2) / cn->height) * util.ecn \
			- (1 + height_ratio) \
			* pow(util.ecn, 2) - pow(radius, 2);
	// util.abc[0] = dot_product(util.ray_dir, util.ray_dir) - 2 * pow(util.ray_dir.y, 2);
	// util.abc[1] = util.ray_dir.x * util.origin.x - util.ray_dir.y * util.origin.y \
				+ util.ray_dir.z * util.origin.z;
	// util.abc[2] = dot_product(util.origin, util.origin) - 2 * pow(util.origin.y, 2);
	util.det = util.abc[1] * util.abc[1] - util.abc[0] * util.abc[2];
	return (util);
}

void	get_cn_solution(t_util *util)
{
	double	temp_t;

	util->t[0] = (-util->abc[1] + sqrt(util->det)) / util->abc[0];
	util->t[1] = (-util->abc[1] - sqrt(util->det)) / util->abc[0];
	if (util->t[0] > util->t[1])
	{
		temp_t = util->t[0];
		util->t[0] = util->t[1];
		util->t[1] = temp_t;
	}
	util->alpha = util->t[0] * util->dn + util->ecn;
	util->beta = util->t[1] * util->dn + util->ecn;
}

double	get_cy_up_hit(t_fig *cy, t_util util)
{
	t_vector	close;
	double		height;
	double		total_dist;
	double		c;
	double		hyp;

	close = find_closest_center(cy, util.origin, util.ray_dir);
	// close =  add_vec(cy->xyz, mul_vec(cy->normal_vec, cy->height));
	height = fabs(dot_product(sub_vec(close, util.origin), \
			cy->normal_vec));
	total_dist = sqrt(dot_product(util.ray_dir, util.ray_dir));
	c = fabs(dot_product(util.ray_dir, cy->normal_vec)) \
			/ total_dist;
	hyp = height / c;
	return (hyp / total_dist);
}
