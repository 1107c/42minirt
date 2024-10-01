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

double	intersect_plane(t_fig *pl, t_xs *xs)
{
	(void)pl;
	if (xs->left == 0)
	{
		if (xs->right == 0)
			return (EPSILON);
		return (-1.0);
	}
	return (xs->right / xs->left);
}

double	intersect_sphere(t_fig *sp, t_xs *xs)
{
	double	temp;

	(void)sp;
	if (xs->det < 0)
		return (-1.0);
	xs->t[0] = (-xs->abc[1] - sqrt(xs->det)) / xs->abc[0];
	xs->t[1] = (-xs->abc[1] + sqrt(xs->det)) / xs->abc[0];
	if (xs->t[0] > xs->t[1])
	{
		temp = xs->t[0];
		xs->t[0] = xs->t[1];
		xs->t[1] = temp;
	}
	if (xs->t[0] > 0)
		return (xs->t[0]);
	if (xs->t[1] > 0)
	{
		xs->flag = 1;
		return (xs->t[1]);
	}
	return (-1.0);
}

double	intersect_cylinder(t_fig *cy, t_xs *xs)
{
	if (fabs(xs->abc[0]) < EPSILON \
		&& fabs(xs->abc[1]) < EPSILON)
		return (parallel_to_cy_norm(cy, xs));
	if (xs->det < 0)
		return (-1.0);
	get_cy_solution(xs);
	if (xs->type == NO_HIT)
		return (-1.0);
	else if (xs->type == SIDE_SIDE_HIT)
		return (cylinder1(cy, xs));
	else if (xs->type == CENTER_SIDE_HIT)
		return (cylinder2(cy, xs));
	else if (xs->type == SIDE_CENTER_HIT)
		return (cylinder3(cy, xs));
	else
		return (cylinder4(cy, xs));
}

double	intersect_cone(t_fig *cn, t_xs *xs)
{
	t_vector	line;

	xs->left = xs->ecn / sqrt(dot_product(\
			xs->from_fig_center, xs->from_fig_center));
	line = normalize_vec(sub_vec(cn->top, xs->from));
	xs->right = dot_product(line, cn->normal_vec);
	if (fabs(xs->abc[0]) < EPSILON \
		&& abs(xs->abc[1] < EPSILON))
		return (parallel_to_cn_norm(xs));
	if (xs->det < 0)
		return (-1.0);
	get_cn_solution(xs);
	if (xs->type == NO_HIT)
		return (-1.0);
	else if (xs->type == SIDE_SIDE_HIT)
		return (cone1(cn, xs));
	else if (xs->type == CENTER_SIDE_HIT)
		return (cone2(cn, xs));
	else if (xs->type == SIDE_CENTER_HIT)
		return (cone3(cn, xs));
	else if (xs->type == CENTER_CENTER_HIT)
		return (cone4(cn, xs));
	else
		return (cone5(cn, xs));
}
