/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:59:08 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/21 12:59:08 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static double	get_traingle_height(t_fig *cy, t_vector point);
static t_vector	get_point(t_vector p1, t_vector p2, double t);

double	handle_cy_positive(t_util util, t_fig *cy, int *flag)
{
	if (util.t[0] < util.t[1])
	{
		if (util.alpha > 0 && util.alpha <= cy->height)
			return (util.t[0]);
		else
		{
			*flag = 1;
			return (find_equation(cy, util, util.t[0], util.t[1]));
		}
	}
	else
	{
		if (util.beta > 0 && util.beta <= cy->height)
			return (util.t[1]);
		else
		{
			*flag = 1;
			return (find_equation(cy, util, util.t[1], util.t[0]));
		}
	}
}

double	find_equation(t_fig *cy, t_util util, double small, double big)
{
	double		c;
	double		tanh;
	double		h;
	double		x;

	c = dot_product(util.ray_dir, cy->normal_vec) \
		/ sqrt(dot_product(util.ray_dir, util.ray_dir));
	if (c < 0)
		c = -c;
	tanh = sqrt(1 - c * c) / c;
	h = get_traingle_height(cy, get_point(util.origin, util.ray_dir, small));
	x = cy->diameter / tanh;
	return (big * h / x + small * (x - h) / x);
}

double	get_traingle_height(t_fig *cy, t_vector point)
{
	t_vector	top;
	t_vector	bottom;
	t_vector	tmp[2];
	double		t[2];
	double		c;

	bottom = cy->xyz;
	top = add_vec(cy->xyz, mul_vec(cy->normal_vec, cy->height));
	tmp[0] = sub_vec(top, point);
	t[0] = sqrt(dot_product(tmp[0], tmp[0]));
	tmp[1] = sub_vec(bottom, point);
	t[1] = sqrt(dot_product(tmp[0], tmp[1]));
	if (t[0] <= t[1])
		c = dot_product(cy->normal_vec, tmp[0]) / t[0];
	else
		c = dot_product(cy->normal_vec, tmp[1]) / t[1];
	if (c < 0)
		c = -c;
	if (t[0] <= t[1])
		return (t[0] * c);
	return (t[1] * c);
}

t_vector	get_point(t_vector p1, t_vector p2, double t)
{
	t_vector	vec;

	vec = add_vec(p1, mul_vec(p2, t));
	return (vec);
}

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
