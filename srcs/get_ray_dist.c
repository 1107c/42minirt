/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  get_ray_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 23:47:18 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	get_cone_normal(t_fig *cn, t_vector p1, t_vector p2, double t)
{
	t_vector	dqec[3];
	double		ecn;
	double		dn;
	double		r;
	double		alpha;

	dqec[0] = sub_vec(p2, p1);
	dqec[2] = sub_vec(p1, cn->xyz);
	ecn = dot_product(dqec[2], cn->normal_vec);
	dn = dot_product(dqec[0], cn->normal_vec);
	alpha = ecn + t * dn;
	r = cn->diameter * (cn->height - alpha) / (2 * cn->height);
	dqec[1] = sub_vec(add_vec(dqec[2], mul_vec(dqec[0], t)), \
		mul_vec(cn->normal_vec, ecn + t * dn));
	dqec[1] = add_vec(mul_vec(cn->normal_vec, r), \
		mul_vec(dqec[1], cn->height - alpha));
	dqec[1] = normalize_vec(dqec[1]);
	return (dqec[1]);
}

double	get_ray_dist_cy(t_vector point, t_fig *fig, t_rt *rt, t_vec *vec)
{
	double	t;
	double	theta;
	int		flg;

	flg = 0;
	t = intersect_cylinder(fig, rt->cam->coords, point, &flg);
	vec->inter_vec = add_vec(rt->cam->coords, \
		mul_vec(sub_vec(point, rt->cam->coords), t));
	if (flg == 1)
		vec->n_vec = fig->normal_vec;
	else
	{
		vec->n_vec = sub_vec(vec->inter_vec, fig->xyz);
		theta = dot_product(vec->n_vec, fig->normal_vec) / \
			sqrt(dot_product(vec->n_vec, vec->n_vec));
		vec->n_vec = sub_vec(vec->n_vec, mul_vec(fig->normal_vec, theta));
		vec->n_vec = normalize_vec(vec->n_vec);
	}
	return (t);
}

double	get_ray_dist(t_vector point, t_fig *fig, t_rt *rt, t_vec *vec)
{
	double	t;

	if (fig->type == PLANE)
		t = intersect_plane(fig, rt->cam->coords, point);
	else if (fig->type == SPHERE)
		t = intersect_sphere(fig, rt->cam->coords, point);
	else if (fig->type == CONE)
		t = intersect_cone(fig, rt->cam->coords, point);
	vec->inter_vec = add_vec(rt->cam->coords, \
		mul_vec(sub_vec(point, rt->cam->coords), t));
	if (fig->type == PLANE)
		vec->n_vec = invert_vec(fig->normal_vec);
	else if (fig->type == SPHERE)
		vec->n_vec = normalize_vec(sub_vec(vec->inter_vec, fig->xyz));
	else if (fig->type == CONE)
		vec->n_vec = get_cone_normal(fig, rt->cam->coords, point, t);
	if (fig->type == CYLINDER)
		return (get_ray_dist_cy(point, fig, rt, vec));
	return (t);
}
