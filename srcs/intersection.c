/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:08:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 14:32:29 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	intersect_plane(t_fig *pl, t_vector cam, t_vector point)
{
	t_vector	vec;
	double		d;
	double		res;

	vec = sub_vec(point, cam);
	d = dot_product(pl->normal_vec, pl->xyz) \
		- dot_product(pl->normal_vec, cam);
	res = dot_product(pl->normal_vec, vec);
	if (res == 0)
	{
		if (d == 0)
			return (0.0);
		return (-1.0);
	}
	return (d / res);
}

double	intersect_sphere(t_fig *sp, t_vector p1, t_vector p2)
{
	t_vector	vec1;
	t_vector	vec2;
	double		det[3];
	double		res;
	double		t[2];

	vec1 = sub_vec(p2, p1);
	vec2 = sub_vec(p1, sp->xyz);
	det[0] = dot_product(vec1, vec1);
	det[1] = dot_product(vec1, vec2);
	det[2] = dot_product(vec2, vec2) - sp->diameter * sp->diameter / 4;
	res = det[1] * det[1] - det[0] * det[2];
	if (fabs(res) > EPSILON && res < 0)
		return (-1.0);
	t[0] = (-det[1] - sqrt(res)) / det[0];
	t[1] = (-det[1] + sqrt(res)) / det[0];
	if (t[0] > 0 && t[0] < t[1])
		return (t[0]);
	if (t[1] > 0)
		return (t[1]);
	return (-1.0);
}

double	intersect_cylinder(t_fig *cy, t_vector p1, t_vector p2, int *flg)
{
	t_util	util;

	util = init_cy_util(cy, p1, p2);
	if (fabs(util.abc[0]) < EPSILON && fabs(util.abc[1]) < EPSILON)
		return (parallel_to_cy_norm(util, cy, p1, p2));
	if (util.det < 0)
		return (-1.0);
	get_cy_solution(&util, cy);
	if ((util.alpha < 0 && util.beta < 0) \
		|| (util.alpha > cy->height && util.beta > cy->height) \
		|| (util.t[0] <= 0 && util.t[1] <= 0))
		return (-1.0);
	if ((util.t[0] > 0 && util.t[1] > 0))
		return (handle_cy_positive(util, cy, flg));
	*flg = 1;
	if (util.t[0] >= 0)
	{
		if (util.beta >= 0 && util.beta <= cy->height)
			return (EPSILON);
		return (get_cy_up_hit(cy, util));
	} 
	if (util.t[1] >= 0)
	{
		if (util.alpha >= 0 && util.alpha <= cy->height)
			return (EPSILON);
		return (get_cy_up_hit(cy, util));
	}
	return (EPSILON);
	return (-1.0);
}

double	intersect_cone(t_fig *cn, t_vector p1, t_vector p2)
{
	t_util	util;

	util = init_cn_util(cn, p1, p2);
	if (fabs(util.abc[0]) < EPSILON && fabs(util.abc[1] < EPSILON))
		return (-1.0);
	if (util.det < 0)
		return (-1.0);
	get_cn_solution(&util);
	if ((util.alpha < 0 && util.beta < 0) || \
		(util.alpha > cn->height && util.beta > cn->height) || \
		(util.t[0] <= 0 && util.t[1] <= 0))
		return (-1.0);
	if ((util.t[0] > 0 && util.t[1] > 0))
		return (handle_cn_positive(util, cn));
	if (util.t[0] >= 0)
		return (util.t[0]);
	return (util.t[1]);
}
