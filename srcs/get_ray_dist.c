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

static double	get_ray_dist_cy(t_rt *rt, t_fig *fig, t_vector point);

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

double	get_ray_dist_cy(t_rt *rt, t_fig *fig, t_vector point)
{
	double	t;
	double	theta;
	int		flg;

	flg = 0;
	// t = intersect_cylinder(fig, rt->cam->coords, point, &flg);
	// vec->inter_vec = add_vec(rt->cam->coords, \
	// 	mul_vec(sub_vec(point, rt->cam->coords), t));
	// if (flg == 1)
	// 	vec->n_vec = fig->normal_vec;
	// else if (flg == 2)
	// 	vec->n_vec = invert_vec(fig->normal_vec);
	// else if (flg == 3)
	// 	vec->n_vec = (t_vector) {0, 0, 0, 0};
	// else
	// {
	// 	vec->n_vec = sub_vec(vec->inter_vec, fig->xyz);
	// 	theta = dot_product(vec->n_vec, fig->normal_vec) / \
	// 		sqrt(dot_product(vec->n_vec, vec->n_vec));
	// 	vec->n_vec = sub_vec(vec->n_vec, mul_vec(fig->normal_vec, theta));
	// 	vec->n_vec = normalize_vec(vec->n_vec);
	// }
	return (t);
}

void	prepare_computation(t_fig *fig, t_xs *xs)
{
	if (fig->type == PLANE)
		plane_xs(fig, xs);
	else if (fig->type == SPHERE)
		sphere_xs(fig, xs);
	else if (fig->type == CYLINDER)
		cylinder_xs(fig, xs);
	else
		cone_xs(fig, xs);
}

double	get_ray_dist(t_fig *fig, t_xs *xs)
{
	prepare_computation(fig, xs);
	if (fig->type == PLANE)
		return (intersect_plane(fig, xs));
	else if (fig->type == SPHERE)
		return (intersect_sphere(fig, xs));
	else if (fig->type == CYLINDER)
		return (intersect_cylinder(fig, xs));
	else
		return (intersect_cone(fig, xs));
}
