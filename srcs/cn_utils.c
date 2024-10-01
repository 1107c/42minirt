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

	return (-1.0);
	if (fabs(xs->abc[2]) >= EPSILON)
		return (-1.0);
	bottom = xs->from_fig_center;
	top = add_vec(bottom, mul_vec(cn->normal_vec, xs->h));
	hit = sub_vec(top, xs->from);
	hit_dist = sqrt(dot_product(hit, hit));
	return (hit_dist / xs->total_dist);
}

void	get_cn_solution(t_fig *cn, t_xs *xs)
{
	t_vector	top;
	t_vector	line;
	double		temp_t;

	xs->t[0] = (-xs->abc[1] + sqrt(xs->det)) / xs->abc[0];
	xs->t[1] = (-xs->abc[1] - sqrt(xs->det)) / xs->abc[0];
	if (xs->t[0] > xs->t[1])
	{
		temp_t = xs->t[0];
		xs->t[0] = xs->t[1];
		xs->t[1] = temp_t;
	}
	xs->alpha = xs->t[0] * xs->dn + xs->ecn;
	xs->beta = xs->t[1] * xs->dn + xs->ecn;
	xs->type = get_cn_type(xs, xs->h / 2);
	xs->left = xs->ecn / sqrt(dot_product( \
			xs->from_fig_center, xs->from_fig_center));
	top = add_vec(cn->xyz, mul_vec(cn->normal_vec, xs->h));
	line = normalize_vec(sub_vec(top, xs->from));
	xs->right = dot_product(line, cn->normal_vec);
}

double	get_cn_center_hit(t_fig *cn, t_xs *xs, t_vector close)
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

int	get_equation_type(double sol, double h1, double h2)
{
	if (sol < 0)
		return (0);
	else if (sol < h1)
		return (1);
	else if (sol <= h2)
		return (2);
	return (3);
}

int	get_cn_type(t_xs *xs, double h)
{
	xs->t_a = get_equation_type(xs->alpha, h, xs->h);
	xs->t_b = get_equation_type(xs->beta, h, xs->h);
	if ((xs->t_a == 0 && xs->t_b == 0) ||
		(xs->t_a == 3 && xs->t_b == 3))
		return (NO_HIT);
	else if ((xs->t_a == 1 && xs->t_b == 1) \
		|| (xs->t_a == 2 && xs->t_b == 2))
		return (SIDE_SIDE_HIT);
	else if ((xs->t_a == 0 && xs->t_b == 1) \
		|| (xs->t_a == 3 && xs->t_b == 2))
		return (CENTER_SIDE_HIT);
	else if ((xs->t_a == 2 && xs->t_b == 3)
		|| (xs->t_a == 1 && xs->t_b == 0))
		return (SIDE_CENTER_HIT);
	else if ((xs->t_a == 1 && xs->t_b == 2) \
		|| (xs->t_a == 2 && xs->t_b == 1))
		return (CENTER_CENTER_HIT);
	else if ((xs->t_a == 0 && xs->t_b == 2) \
		|| (xs->t_a == 3 && xs->t_b == 1) \
		|| (xs->t_a == 1 && xs->t_b == 3) \
		|| (xs->t_a == 2 && xs->t_b == 0))
		return (SIDE_HIT);
	return (NO_HIT);
}
