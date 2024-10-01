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

t_vector	get_cone_normal(t_fig *cn, t_xs *xs, double time)
{
	t_vector	dqec;
	double		r;

	if (xs->flag == 1)
		return (cn->normal_vec);
	else if (xs->flag == 2)
		return (invert_vec(cn->normal_vec));
	else if (xs->flag == 3)
		return (init_vector(0, 0, 0));
	r = cn->diameter * (cn->height - xs->alpha) \
		/ xs->h;
	dqec = sub_vec(add_vec(xs->from_fig_center, \
			mul_vec(xs->ray_dir, time)), \
			mul_vec(cn->normal_vec, xs->ecn \
			+ time * xs->dn));
	dqec = add_vec(mul_vec(cn->normal_vec, r), \
			mul_vec(dqec, cn->height - xs->alpha));
	dqec = normalize_vec(dqec);
	return (dqec);
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
