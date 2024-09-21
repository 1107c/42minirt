/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 23:47:18 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	get_sphere_uv(double uv[2], t_fig *fig, t_rt *rt)
{
	t_vector	point;

	point = normalize_vec(sub_vec(rt->vec.inter_vec, fig->xyz));
	uv[0] = 0.5 + (atan2(point.z, point.x)) / (2 * M_PI);
	uv[1] = 0.5 + asin(point.y) / M_PI;
}

void	get_plane_uv(t_vector inter_vec, t_fig *fig, double *u, double *v)
{
	t_vector	tmp;
	double		u2[2];
	double		v2[2];
	double		det;

	u2[0] = fig->right_vec.x;
	u2[1] = fig->right_vec.y;
	v2[0] = fig->up_vec.x;
	v2[1] = fig->up_vec.y;
	tmp = sub_vec(inter_vec, fig->xyz);
	if (fig->right_vec.x == 0 && fig->up_vec.x == 0)
	{
		u2[0] = fig->right_vec.z;
		v2[0] = fig->up_vec.z;
		tmp.x = tmp.z;
	}
	if (fig->right_vec.y == 0 && fig->up_vec.y == 0)
	{
		u2[1] = fig->right_vec.z;
		v2[1] = fig->up_vec.z;
		tmp.y = tmp.z;
	}
	det = u2[0] * v2[1] - u2[1] * v2[0];
	*u = 0.05 * (v2[1] * tmp.x - v2[0] * tmp.y) / det;
	*v = 0.05 * (-u2[1] * tmp.x - u2[0] * tmp.y) / det;
}

void	get_cylinder_uv(t_vector point, double uv[2], t_fig *fig, t_rt *rt, double t)
{
	double	theta;
	double	raw_u;
	// double	u1;
	// double	v1;
	double	dn = dot_product(sub_vec(point, rt->cam->coords), \
				 fig->normal_vec);
	double	h = dot_product(rt->cam->coords, fig->normal_vec) \
				+ t * dn \
				- dot_product(fig->xyz, fig->normal_vec);
	t_vector	p;
	p = add_vec(fig->xyz, mul_vec(fig->normal_vec, h));
	p = sub_vec(rt->vec.inter_vec, p);
	p = normalize_vec(p);
	// u1 = p.x;
	// v1 = p.z;
	// if (fabs(p.x) < EPSILON)
	// 	u1 = p.y;
	// if (fabs(p.z) < EPSILON)
	// 	v1 = p.y;
	(void) h;
	// theta = atan2(u1, v1);
	theta = atan2(p.x, p.z);
	raw_u = theta / (2 * M_PI);
	// printf("theta, raw_u: %lf, %lf\n", theta, raw_u);
	uv[0] = 1 - (raw_u + 0.5);
	// *v = h - floor(h);
	uv[1] = p.y - floor(p.y);
	// printf("u, v: %lf %lf\n", *u, *v);
	// *u *= 0.05;
	// *v *= 0.05;
}
