/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils_cy1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:08:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 14:32:29 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
// a', b', c' => 실린더의 center점(CY)
// a'', b'', c'' => 실린더의 normal_vec(CYN)
// a, b, c => 카메라의 위치(C)
// p, q, r => 카메라의 ray의 방향벡터(CN)
// A = dot_product(CYN, CN)
// B = -dot_product(CN, CN)
// C = dot_product(CYN, CYN)
// D = -dot_product(A)
// E = dot_product(C - CY, CN)
// F = dot_product(C - CY, CYN)

double	find_eqution(t_fig *cy, t_util util, double small, double big)
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

t_vector	get_point(t_vector p1, t_vector p2, double t)
{
	t_vector	p;

	p = add_vec(p1, mul_vec(p2, t));
	return (p);
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

t_vector	get_closest_center(t_fig *cy, t_vector point)
{
	t_vector	top;
	t_vector	bottom;
	t_vector	t[2];
	double		dist[2];

	bottom = cy->xyz;
	top = add_vec(cy->xyz, mul_vec(cy->normal_vec, cy->height));
	t[0] = sub_vec(bottom, point);
	t[1] = sub_vec(top, point);
	dist[0] = dot_product(t[0], t[0]);
	dist[1] = dot_product(t[1], t[1]);
	if (dist[0] < dist[1])
		return (bottom);
	return (top);
}

double	get_parallel_norm_hit(t_fig *cy, t_vector point, t_vector end)
{
	t_vector	closer_area;
	t_vector	t[2];
	double		height;
	double		total_dist;

	closer_area = get_closest_center(cy, point);
	t[0] = sub_vec(closer_area, point);
	height = fabs(dot_product(t[0], cy->normal_vec));
	t[1] = sub_vec(end, point);
	total_dist = sqrt(dot_product(t[1], t[1]));
	return (height / total_dist);
}
