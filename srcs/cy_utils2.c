/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:47:48 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/29 21:47:48 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <complex.h>

int	is_in_cylinder(t_fig *cy, t_xs *xs)
{
	t_vector	dt;
	double		h_sq;
	double		dot;
	double		dsq;

	h_sq = pow(xs->h, 2);
	dt = mul_vec(cy->normal_vec, cy->height);
	dot = dot_product(dt, xs->from_fig_center);
	if (dot < 0.0 || dot > h_sq)
		return (0);
	dsq = dot_product(xs->from_fig_center, xs->from_fig_center) \
		- pow(dot, 2) / h_sq;
	if (dsq > cy->radius_sq)
		return (0);
	return (1);
}

double	test2(t_fig *cy, t_xs *xs, t_vector close)
{
	t_vector	line;
	double		c;
	double		h;
	double		c1;
	double		total;

	line = sub_vec(xs->from, close);
	c = fabs(dot_product(cy->normal_vec, line));
	h = sqrt(dot_product(line, line)) * c;
	c1 = fabs(dot_product(cy->normal_vec, xs->ray_dir));
	total = sqrt(dot_product(xs->ray_dir, xs->ray_dir));
	return (h / (total * c1));
}

int	is_height(t_fig *cy, t_xs *xs)
{
	t_vector	front_intersect;
	t_vector	temp;
	double		c;
	double		h;

	front_intersect = add_vec(xs->from, \
		mul_vec(xs->ray_dir, xs->t[1]));
	c = fabs(dot_product(xs->ray_dir, cy->normal_vec) \
		/ sqrt(dot_product(xs->ray_dir, xs->ray_dir)));
	temp = sub_vec(front_intersect, xs->from);
	h = sqrt(dot_product(temp, temp)) * c;
	if (xs->beta < 0 && h <= fabs(xs->beta))
		return (1);
	if (xs->beta > cy->height && xs->beta - h >= cy->height)
		return (1);
	return (0);
}
