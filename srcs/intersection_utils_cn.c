/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils_cn.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:08:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 14:32:29 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	handle_cn_positive(t_util util, t_fig *cn)
{
	if (util.t[0] < util.t[1])
	{
		if (util.alpha > 0 && util.alpha <= cn->height)
			return (util.t[0]);
		else
			return (util.t[1]);
	}
	else
	{
		if (util.beta > 0 && util.beta <= cn->height)
			return (util.t[1]);
		else
			return (util.t[0]);
	}
}

// dn = dot_product(vec1, cy->normal_vec);
// ecn = dot_product(cy->normal_vec, vec2);
// ecd = dot_product(vec1, vec2);
// det[0] = dot_product(vec1, vec1) - (1 + pow(cy->diameter / 2, 2) / pow(cy->height, 2)) * pow(dn, 2);
// det[1] = ecd + (pow(cy->diameter / 2, 2) / cy->height) * dn
// 		- (1 + pow(cy->diameter / 2, 2) / pow(cy->height, 2)) * ecn * dn;
// det[2] = dot_product(vec2, vec2) + 2 * (pow(cy->diameter / 2, 2) / cy->height) * ecn
// 		- (1 + pow(cy->diameter / 2, 2) / pow(cy->height, 2)) * pow(ecn, 2) - pow(cy->diameter / 2, 2);
// res = det[1] * det[1] - det[0] * det[2];

t_util	init_cn_util(t_fig *cn, t_vector p1, t_vector p2)
{
	t_util	util;

	util.origin = p1;
	util.ray_dir = sub_vec(p2, p1);
	util.from_fig_center = sub_vec(p1, cn->xyz); // ec
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
