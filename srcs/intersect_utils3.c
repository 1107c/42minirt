/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_xss3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:01:35 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/21 13:01:35 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/*
t_xs		init_cn_util(t_fig *cn, t_vector p1, t_vector p2)
{
	t_xs	util;
	double	radius;
	double	height_ratio;

	 util.origin = p1;
	util.ray_dir = sub_vec(p2, p1);
	 d = sub_vec(util.ray_dir, cn->normal_vec);
	 radius = cn->diameter / 2;
	 apex = add_vec(cn->xyz, mul_vec(cn->normal_vec, cn->height));
	 h = cn->height;
	 util.abc[0] = d.x * d.x + d.y * d.y - (radius * radius) / (h * h) * d.z * d.z;
	 util.abc[1] = d.x * (util.origin.x - apex.x) + d.y * (util.origin.y - apex.y) -
	 			(radius * radius) / (h * h) * d.z * (util.origin.z - apex.z);
	 util.abc[2] = (util.origin.x - apex.x) * (util.origin.x - apex.x) +
				(util.origin.y - apex.y) * (util.origin.y - apex.y) -
				(radius * radius) / (h * h) * (util.origin.z - apex.z) * (util.origin.z - apex.z);
	util.from_fig_center = sub_vec(p1, cn->xyz);
	util.dn = dot_product(util.ray_dir, cn->normal_vec);
	util.ecn = dot_product(cn->normal_vec, util.from_fig_center);
	util.ecd = dot_product(util.ray_dir, util.from_fig_center);
	radius = cn->diameter / 2;
	height_ratio = pow(radius / cn->height, 2);
	util.abc[0] = dot_product(util.ray_dir, util.ray_dir) - \
				(1 + height_ratio) \
				* pow(util.dn, 2);
	util.abc[1] = util.ecd - util.ecn * util.dn * (1 + height_ratio) \
				+ height_ratio * cn->height * util.dn;
	util.abc[2] = dot_product(util.from_fig_center, util.from_fig_center) \
			+ 2 * (pow(radius, 2) / cn->height) * util.ecn \
			- (1 + height_ratio) \
			* pow(util.ecn, 2) - pow(radius, 2);
	util.c = cn->height / sqrt(pow(radius, 2) + pow(cn->height, 2));
	util.h = cn->height * 2;
	 util.abc[0] = dot_product(util.ray_dir, util.ray_dir) - 2 * pow(util.ray_dir.y, 2);
	 util.abc[1] = util.ray_dir.x * util.origin.x - util.ray_dir.y * util.origin.y \
				+ util.ray_dir.z * util.origin.z;
	 util.abc[2] = dot_product(util.origin, util.origin) - 2 * pow(util.origin.y, 2);
	util.det = util.abc[1] * util.abc[1] - util.abc[0] * util.abc[2];
	return (util);
	}*/

void	get_cn_solution(t_xs *xs)
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
	xs->alpha = xs->t[0] * xs->dn + xs->ecn;
	xs->beta = xs->t[1] * xs->dn + xs->ecn;
}
