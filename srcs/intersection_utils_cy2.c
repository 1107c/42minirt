/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils_cy2.c                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:08:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 14:32:29 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
// dist = dot_product(vec2, vec3) / sqrt(dot_product(vec3, vec3));
// if (dist < 0)
// 	dist = -dist;
// res = dot_product(vec1, cy->normal_vec) / dot_product(vec1, vec1);
// if ((res == 1 || res == -1) && dist <= cy->diameter / 2)
// 	return (get_parallel_norm_hit(cy, p1, p2));

// vec1 = sub_vec(p2, p1); // d
// vec2 = sub_vec(p1, cy->xyz); // e - c
// vec3 = cross_product(vec1, cy->normal_vec);
// dn = dot_product(vec1, cy->normal_vec);
// det[0] = dot_product(vec1, vec1) - dn * dn;
// det[1] = dot_product(vec1, vec2) - dot_product(vec2, cy->normal_vec) * dn;
// det[2] = dot_product(vec2, vec2) - dot_product(vec2, cy->normal_vec) *
// 		dot_product(vec2, cy->normal_vec) - (cy->diameter * cy->diameter) / 4;

t_util	init_cy_util(t_fig *cy, t_vector p1, t_vector p2)
{
	t_util	util;

	util.origin = p1;
	util.ray_dir = sub_vec(p2, p1);
	util.from_fig_center = sub_vec(p1, cy->xyz); // ec
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

void	get_cy_solution(t_util *util, t_fig *cy)
{
	util->t[0] = (-util->abc[1] + sqrt(util->det)) / util->abc[0];
	util->t[1] = (-util->abc[1] - sqrt(util->det)) / util->abc[0];
	util->alpha = dot_product(util->origin, cy->normal_vec) \
				+ util->t[0] * util->dn \
				- dot_product(cy->xyz, cy->normal_vec);
	util->beta = util->alpha + (util->t[1] - util->t[0]) * util->dn;
}

double	handle_cy_positive(t_util util, t_fig *cy, int *flag)
{
	if (util.t[0] < util.t[1])
	{
		// 옆
		if (util.alpha > 0 && util.alpha <= cy->height)
			return (util.t[0]);
		// 위
		else
		{
			*flag = 1;
			return (find_eqution(cy, util, util.t[0], util.t[1]));
		}
	}
	else
	{
		if (util.beta > 0 && util.beta <= cy->height) // 옆면
			return (util.t[1]);
		else //위
		{
			*flag = 1;
			return (find_eqution(cy, util, util.t[1], util.t[0]));
		}
	}
}
