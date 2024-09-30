/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:50:47 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/29 21:50:47 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/* 수정 필요 */
double	parallel_to_cn_norm(t_fig *cn, t_xs *xs)
{
	t_vector	bottom;
	t_vector	top;
	t_vector	hit;
	double		hit_dist;

	if (fabs(xs->abc[2]) >= EPSILON)
		return (-1.0);
	bottom = xs->from_fig_center;
	top = add_vec(bottom, mul_vec(cn->normal_vec, xs->h));
	hit = sub_vec(top, xs->from);
	hit_dist = sqrt(dot_product(hit, hit));
	return (hit_dist / xs->total_dist);
}

double	cone1(t_fig *cn, t_xs *xs, t_vector close)
{
	t_vector	temp;
	double		c;
	double		h;
	double		hit_dist;

	temp = sub_vec(close, xs->from);
	h = fabs(dot_product(temp, cn->normal_vec));
	c = fabs(dot_product(xs->ray_dir, cn->normal_vec)) \
		/ xs->total_dist;
	hit_dist = h / c;
	return (hit_dist / xs->total_dist);
}
