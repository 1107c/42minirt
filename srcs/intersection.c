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

double		intersect_sphere(t_fig *sp, t_vector p1, t_vector p2, int *flag)
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
	if (res < 0)
		return (-1.0);
	t[0] = (-det[1] - sqrt(res)) / det[0];
	t[1] = (-det[1] + sqrt(res)) / det[0];
	if (t[0] > 0 && t[0] < t[1])
		return (t[0]);
	if (t[1] > 0)
	{
		if (t[0] < t[1])
		{
			*flag = 1;
			return (t[1]);
		}
	}
	return (-1.0);
}

double	cylinder1(t_fig *cy, t_util util, int *flag)
{
	t_vector	first;
	t_vector	second;
	double		d[2];
	double		t;

	first = sub_vec(cy->xyz, util.origin);
	second = sub_vec(add_vec(cy->xyz, \
			mul_vec(cy->normal_vec, cy->height)), util.origin);
	// d = dot_product(first, second);
	d[0] = dot_product(util.origin, first);
	d[1] = dot_product(util.origin, second);
	// 실린더 내부에서 광선을 쏜 경우(ok)
	if (dot_product(first, second) < 0)
	{
		*flag = 3;
			return (util.t[1]);
	}
	// return (EPSILON);
	// 실린더 외부(ok)
	else
	{
		// printf("alpha, beta: %lf %lf\n", util.alpha, util.beta);
		if (util.alpha < 0)
		{
			*flag = 2;
		}
		else
			*flag = 1;
		return (get_cy_up_hit(cy, util));
	}
}

double	test(t_fig *cy, t_util util)
{
	t_vector	back_intersect;
	t_vector	temp;
	double		c;
	double		h;
	double		h1;

	back_intersect = add_vec(util.origin, \
					mul_vec(util.ray_dir, util.t[0]));
	c = fabs(dot_product(util.ray_dir, cy->normal_vec) \
		/ sqrt(dot_product(util.ray_dir, util.ray_dir)));
	temp = sub_vec(back_intersect, util.origin);
	if (util.alpha < 0)
		h = cy->height - (sqrt(dot_product(temp, temp)) \
			* c + util.alpha);
	else
		h = cy->height - (util.alpha - \
			sqrt(dot_product(temp, temp)) * c);
	h1 = sqrt(dot_product(util.ray_dir, util.ray_dir)) * c;
	return (h / h1);
}

int	is_height(t_fig *cy, t_util util)
{
	t_vector	front_intersect;
	t_vector	temp;
	double		c;
	double		h;
	double		h1;

	front_intersect = add_vec(util.origin, \
					mul_vec(util.ray_dir, util.t[1]));
	c = fabs(dot_product(util.ray_dir, cy->normal_vec) \
		/ sqrt(dot_product(util.ray_dir, util.ray_dir)));
	temp = sub_vec(front_intersect, util.origin);
	h = sqrt(dot_product(temp, temp)) * c;
	if (util.beta < 0 && h <= fabs(util.beta))
		return (1);
	if (util.beta > cy->height && util.beta - h >= cy->height)
		return (1);
	return (0);
}

double	test2(t_fig *cy, t_util util, t_vector close)
{
	t_vector	line;
	double		c;
	double		h;
	double		c1;
	double		total;

	line = sub_vec(util.origin, close);
	c = fabs(dot_product(cy->normal_vec, line));
	h = sqrt(dot_product(line, line)) * c;
	c1 = fabs(dot_product(cy->normal_vec, util.ray_dir));
	total = sqrt(dot_product(util.ray_dir, util.ray_dir));
	return (h / (total * c1));
}

double	cylinder2(t_fig *cy, t_util util, int *flag)
{
	t_vector	first;
	t_vector	second;
	double		d[2];

	first = sub_vec(cy->xyz, util.origin);
	second = sub_vec(add_vec(cy->xyz, \
			mul_vec(cy->normal_vec, cy->height)), util.origin);
	d[0] = dot_product(util.ray_dir, first);
	d[1] = dot_product(util.ray_dir, second);
	// 실린더 외부1
	if (d[0] > 0 && d[1] > 0)
	{
		if (util.alpha < 0)
			*flag = 2;
		else
			*flag = 1;
		return (get_cy_up_hit(cy, util));
	}
	// 실린더 외부2
	else if (is_height(cy, util))
		return (-1.0);
	*flag = 3;
	return test2(cy, util, find_closest_center(cy, util.origin, util.ray_dir));
}

double	cylinder3(t_fig *cy, t_util util, int *flag)
{
	// 실린더 내부(ok)
	if (util.t[0] < 0)
	{
		*flag = 3;
		return (util.t[1]);
	}
	// 실린더 외부(ok)
	return (util.t[0]);
}

double	cylinder4(t_fig *cy, t_util util, int *flag)
{
	t_vector	first;
	t_vector	second;
	double		d[2];

	first = sub_vec(cy->xyz, util.origin);
	second = sub_vec(add_vec(cy->xyz, \
			mul_vec(cy->normal_vec, cy->height)), util.origin);
	d[0] = dot_product(util.ray_dir, first);
	d[1] = dot_product(util.ray_dir, second);
	// 실린더 외부1(ok)
	if (util.t[0] > 0)
		return (util.t[0]);
	// 실린더 외부2(ok)
	else if (is_height(cy, util))
		return (-1.0);
	// 실린더 내부
	else if (util.beta <= 0)
	{
		*flag = 3;
		return (test2(cy, util, cy->xyz));
	}
	else
	{
		*flag = 3;
		return (test2(cy, util, add_vec(cy->xyz, \
				mul_vec(cy->normal_vec, cy->height))));
	}
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
		|| (util.t[0] <= EPSILON && util.t[1] <= EPSILON))
		return (-1.0);
	if ((util.alpha < 0 || util.alpha > cy->height) \
		&& (util.beta > 0 && util.beta < cy->height))
		return (cylinder1(cy, util, flg));
	else if ((util.alpha < 0 && util.beta > cy->height) \
		|| (util.alpha > cy->height && util.beta < 0))
		return (cylinder2(cy, util, flg));
	else if ((util.alpha >= 0 && util.alpha <= cy->height) \
		&& (util.beta >= 0 && util.beta <= cy->height))
		return (cylinder3(cy, util, flg));
	else if ((util.alpha > 0 && util.alpha < cy->height) \
		&& (util.beta < 0 || util.beta > cy->height))
		return (cylinder4(cy, util, flg));
	return (-1.0);
}

double	parallel_to_cn_norm(t_util util, t_fig *cn)
{
	t_vector	top;
	t_vector	hit;
	double		total_dist;
	double		hit_dist;

	if (fabs(util.abc[2]) >= EPSILON)
		return (-1.0);
	return (EPSILON);
	top = add_vec(cn->xyz, mul_vec(cn->normal_vec, cn->height));
	hit = sub_vec(top, util.origin);
	hit_dist = sqrt(dot_product(hit, hit));
	total_dist = sqrt(dot_product(util.ray_dir, util.ray_dir));
	return (hit_dist / total_dist);
}

double	test3(t_fig *cn, t_util util)
{
	t_vector	temp;
	double		c;
	double		h;
	double		total_dist;
	double		hit_dist;

	temp = sub_vec(cn->xyz, util.origin);
	h = fabs(dot_product(temp, cn->normal_vec));
	total_dist = sqrt(dot_product(util.ray_dir, \
				util.ray_dir));
	c = fabs(dot_product(util.ray_dir, cn->normal_vec)) \
		/ total_dist;
	hit_dist = h / c;
	return (hit_dist / total_dist);
}

double	cone1(t_util util, t_fig *cn, t_vector close)
{
	t_vector	temp;
	double		c;
	double		h;
	double		total_dist;
	double		hit_dist;

	temp = sub_vec(close, util.origin);
	h = fabs(dot_product(temp, cn->normal_vec));
	total_dist = sqrt(dot_product(util.ray_dir, \
				util.ray_dir));
	c = fabs(dot_product(util.ray_dir, cn->normal_vec)) \
		/ total_dist;
	hit_dist = h / c;
	return (hit_dist / total_dist);
}

double	intersect_cone(t_fig *cn, t_vector p1, t_vector p2)
{
	t_util	util;

	util = init_cn_util(cn, p1, p2);
	if (fabs(util.abc[0]) < EPSILON && fabs(util.abc[1] < EPSILON))
		return (parallel_to_cn_norm(util, cn));
	if (util.det < 0)
		return (-1.0);
	get_cn_solution(&util);
	if (util.alpha < 0 && util.beta < 0)
		return (-1.0);
	if (util.alpha > util.h && util.beta > util.h)
		return (-1.0);
	if (util.t[0] > 0)
	{
		if (util.alpha <= util.h && util.alpha >= 0)
			return (util.t[0]);
		if (util.beta >= 0 && util.beta <= util.h)
			return (util.t[1]);
		return (-1.0);
	}
	else
	{
		double	d;
		double	e;
		double	f;

		d = dot_product(util.ray_dir, sub_vec(cn->xyz, util.origin));
		e = dot_product(util.ray_dir, sub_vec(add_vec(cn->xyz, \
			mul_vec(cn->normal_vec, 2 * cn->height)), util.origin));
		f = util.dn / sqrt(dot_product(util.ray_dir, util.ray_dir));
		if (util.t[1] > 0)
		{
			if (util.beta <= util.h && util.beta >= 0)
				return (util.t[1]);
			// return (-1.0);
			if (util.alpha > 0 && util.beta < 0 \
				&& fabs(f) <= util.c && d >= 0 && e < 0)
				return (cone1(util, cn, cn->xyz));
			// return (EPSILON);
			if (util.alpha < util.h && util.beta > util.h \
				&& fabs(f) <= util.c && e >= 0 && d < 0)
				return (cone1(util, cn, add_vec(cn->xyz, \
					mul_vec(cn->normal_vec, 2 * cn->height))));
		}
		else
		{
			if (fabs(f) >= util.c && d >= 0 && e < 0)
				return (cone1(util, cn, cn->xyz));
			// return (EPSILON);
			if (fabs(f) >= util.c && e >= 0 && d < 0)
				return (cone1(util, cn, add_vec(cn->xyz, \
					mul_vec(cn->normal_vec, 2 * cn->height))));
			// printf("%lf %lf\n", fabs(f), util.c);
			// if (fabs(f) < util.c)
				// return (EPSILON);
		}
	}
	return (-1.0);
}
