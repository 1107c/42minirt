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

t_util	init_cn_util(t_fig *cn, t_vector p1, t_vector p2)
{
	t_util	util;

	util.origin = p1;
	util.ray_dir = sub_vec(p2, p1);
	util.from_fig_center = sub_vec(p1, cn->xyz);
	util.dn = dot_product(util.ray_dir, cn->normal_vec);
	util.ecn = dot_product(cn->normal_vec, util.from_fig_center);
	util.ecd = dot_product(util.ray_dir, util.from_fig_center);
	util.abc[0] = dot_product(util.ray_dir, util.ray_dir) - \
				(1 + pow(cn->diameter / 2, 2) / pow(cn->height, 2)) \
				* pow(util.dn, 2);
	util.abc[1] = util.ecd + util.dn * ((pow(cn->diameter / 2, 2) / cn->height) \
			- (1 + pow(cn->diameter / 2, 2) / pow(cn->height, 2)) * util.ecn);
	util.abc[2] = dot_product(util.from_fig_center, util.from_fig_center) \
			+ 2 * (pow(cn->diameter / 2, 2) / cn->height) * util.ecn \
			- (1 + pow(cn->diameter / 2, 2) / pow(cn->height, 2)) \
			* pow(util.ecn, 2) - pow(cn->diameter / 2, 2);
	util.det = util.abc[1] * util.abc[1] - util.abc[0] * util.abc[2];
	return (util);
}

void	get_cn_solution(t_util *util)
{
	util->t[0] = (-util->abc[1] + sqrt(util->det)) / util->abc[0];
	util->t[1] = (-util->abc[1] - sqrt(util->det)) / util->abc[0];
	util->alpha = util->t[0] * util->dn + util->ecn;
	util->beta = util->alpha + (util->t[1] - util->t[0]) * util->dn;
}

double	get_cy_up_hit(t_fig *cy, t_util util)
{
	t_vector	close;
	double		height;
	double		total_dist;
	double		c;
	double		hyp;

	close = find_closest_center(cy, util.origin);
	height = fabs(dot_product(sub_vec(close, util.origin), \
			cy->normal_vec));
	total_dist = sqrt(dot_product(util.ray_dir, util.ray_dir));
	c = fabs(dot_product(util.ray_dir, cy->normal_vec)) \
			/ total_dist;
	hyp = height / c;
	return (hyp / total_dist);
}
