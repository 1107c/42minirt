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
static int	is_in_cylinder(t_fig *cy, t_xs *xs);

double	cylinder1(t_fig *cy, t_xs *xs)
{
	// return (EPSILON);
	// return (-1.0);
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
	if (is_in_cylinder(cy, xs))
	{
		xs->flag = 3;
		return (get_cy_up_hit(cy, xs));
	}
	if ((xs->beta < 0 && xs->ecn >= 0 && xs->dn <= 0) \
		|| (xs->beta > xs->h && xs->ecn < 0 && xs->dn >= 0))
		{
			printf("%lf %lf\n", xs->beta, xs->ecn);
		return (-1.0);
		}
	if (xs->alpha < 0)
		xs->flag = 2;
	else
		xs->flag = 1;
	return (get_cy_up_hit(cy, xs));
}

double	cylinder3(t_fig *cy, t_xs *xs)
{
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
