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

double	parallel_to_cn_norm(t_xs *xs)
{
	if (fabs(xs->abc[2]) >= EPSILON)
		return (-1.0);
	if (xs->left >= xs->c && xs->left >= xs->c)
		return (EPSILON);
	return (-1.0);
}

void	get_cn_solution(t_xs *xs)
{
	double	temp_t;

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
}

double	get_cn_center_hit(t_fig *cn, t_xs *xs, t_vector close)
{
	t_vector	line;
	double		c;
	double		height;
	double		hit_dist;

	line = sub_vec(close, xs->from);
	height = fabs(dot_product(line, cn->normal_vec));
	c = fabs(dot_product(xs->ray_dir, cn->normal_vec)) \
		/ xs->total_dist;
	hit_dist = height / c;
	return (hit_dist / xs->total_dist);
}

int	get_equation_type(double sol, double h1, double h2)
{
	if (sol < 0)
		return (BOTTOM);
	else if (sol < h1)
		return (LOW_MID);
	else if (sol <= h2)
		return (HIGH_MID);
	return (TOP);
}

int	get_cn_type(t_xs *xs, double h)
{
	xs->t_a = get_equation_type(xs->alpha, h, xs->h);
	xs->t_b = get_equation_type(xs->beta, h, xs->h);
	if ((xs->t_a == BOTTOM && xs->t_b == BOTTOM) \
		|| (xs->t_a == TOP && xs->t_b == TOP))
		return (NO_HIT);
	else if ((xs->t_a == LOW_MID && xs->t_b == LOW_MID) \
		|| (xs->t_a == HIGH_MID && xs->t_b == HIGH_MID))
		return (SIDE_SIDE_HIT);
	else if ((xs->t_a == BOTTOM && xs->t_b == LOW_MID) \
		|| (xs->t_a == TOP && xs->t_b == HIGH_MID))
		return (CENTER_SIDE_HIT);
	else if ((xs->t_a == HIGH_MID && xs->t_b == TOP)
		|| (xs->t_a == LOW_MID && xs->t_b == BOTTOM))
		return (SIDE_CENTER_HIT);
	else if ((xs->t_a == LOW_MID && xs->t_b == HIGH_MID) \
		|| (xs->t_a == HIGH_MID && xs->t_b == LOW_MID))
		return (CENTER_CENTER_HIT);
	else if ((xs->t_a == BOTTOM && xs->t_b == HIGH_MID) \
		|| (xs->t_a == TOP && xs->t_b == LOW_MID) \
		|| (xs->t_a == LOW_MID && xs->t_b == TOP) \
		|| (xs->t_a == HIGH_MID && xs->t_b == BOTTOM))
		return (SIDE_HIT);
	return (NO_HIT);
}
