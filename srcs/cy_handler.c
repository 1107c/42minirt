/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 20:45:37 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/29 21:47:01 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static double	get_cy_hit_dist(t_fig *cy, t_xs *xs, t_vector close);

double	cylinder1(t_fig *cy, t_xs *xs)
{
	t_vector	first;
	t_vector	second;

	first = sub_vec(cy->xyz, xs->from);
	second = sub_vec(add_vec(cy->xyz, \
			mul_vec(cy->normal_vec, cy->height)), xs->from);
	// 실린더 내부에서 광선을 쏜 경우(ok)
	if (dot_product(first, second) < 0)
	{
		xs->flag = 3;
		return (xs->t[1]);
	}
	// 실린더 외부(ok)
	else
	{
		if (xs->alpha < 0)
			xs->flag = 2;
		else
			xs->flag = 1;
		return (get_cy_up_hit(cy, xs));
	}
}

double	cylinder2(t_fig *cy, t_xs *xs)
{
	t_vector	first;
	t_vector	second;
	double		d[2];

	first = sub_vec(cy->xyz, xs->from);
	second = sub_vec(add_vec(cy->xyz, \
			mul_vec(cy->normal_vec, cy->height)), xs->from);
	d[0] = dot_product(xs->ray_dir, first);
	d[1] = dot_product(xs->ray_dir, second);
	// 실린더 외부1
	if (d[0] > 0 && d[1] > 0)
	{
		if (xs->alpha < 0)
			xs->flag = 2;
		else
			xs->flag = 1;
		return (get_cy_up_hit(cy, xs));
	}
	// 실린더 외부2
	else if (dot_product(first, second) < 0)
		return (-1.0);
	xs->flag = 3;
	return (get_cy_hit_dist(cy, xs, \
		find_closest_center(cy, xs->from, xs->ray_dir)));
}

double	cylinder3(t_fig *cy, t_xs *xs)
{
	if (!cy)
		return  (0);
	// 실린더 내부(ok)
	if (xs->t[0] < 0)
	{
		xs->flag = 3;
		return (xs->t[1]);
	}
	// 실린더 외부(ok)
	return (xs->t[0]);
}

double	cylinder4(t_fig *cy, t_xs *xs)
{
	t_vector	first;
	t_vector	second;
	// double		d[2];

	first = sub_vec(cy->xyz, xs->from);
	second = sub_vec(add_vec(cy->xyz, \
			mul_vec(cy->normal_vec, cy->height)), xs->from);
	// d[0] = dot_product(xs->ray_dir, first);
	// d[1] = dot_product(xs->ray_dir, second);
	// 실린더 외부1(ok)
	if (xs->t[0] > 0)
		return (xs->t[0]);
	// 실린더 외부2(ok)
	else if (dot_product(first, second) > 0)
		return (-1.0);
	// 실린더 내부
	xs->flag = 3;
	if (xs->beta <= 0)
		return (get_cy_hit_dist(cy, xs, cy->xyz));
	return (get_cy_hit_dist(cy, xs, add_vec(cy->xyz, \
			mul_vec(cy->normal_vec, cy->height))));
}

double	get_cy_hit_dist(t_fig *cy, t_xs *xs, t_vector close)
{
	t_vector	line;
	double		h;
	double		c;
	double		c1;

	line = sub_vec(xs->from, close);
	c = fabs(dot_product(cy->normal_vec, line));
	h = sqrt(dot_product(line, line)) * c;
	c1 = fabs(dot_product(cy->normal_vec, xs->ray_dir));
	return (h / (xs->total_dist * c1));
}
