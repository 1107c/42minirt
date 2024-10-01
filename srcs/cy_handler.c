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

double	cylinder1(t_fig *cy, t_xs *xs)
{
	if (is_in_cylinder(cy, xs))
	{
		xs->flag = 3;
		return (xs->t[1]);
	}
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
	if (d[0] > 0 && d[1] > 0) 	// 실린더 외부1
	{
		if (xs->alpha < 0)
			xs->flag = 2;
		else
			xs->flag = 1;
		return (get_cy_up_hit(cy, xs));
	}
	else if (is_height(cy, xs))
		return (-1.0);
	xs->flag = 3;
	return (test2(cy, xs, find_closest_center(cy, xs->from, xs->dn)));
}

double	cylinder3(t_fig *cy, t_xs *xs)
{
	(void)cy;
	if (xs->t[0] < 0)
	{
		xs->flag = 3;
		return (xs->t[1]);
	}
	return (xs->t[0]);
}

double	cylinder4(t_fig *cy, t_xs *xs)
{
	if (xs->t[0] > 0)
		return (xs->t[0]);
	if (is_in_cylinder(cy, xs))
	{
		xs->flag = 3;
		return (get_cy_up_hit(cy, xs));
	}
	return (-1.0);
}
