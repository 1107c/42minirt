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
	if (!pl)
		return (0);
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
	if (!sp)
		return (0);
	if (xs->det < 0)
		return (-1.0);
	xs->t[0] = (-xs->abc[1] - sqrt(xs->det)) / xs->abc[0];
	xs->t[1] = (-xs->abc[1] + sqrt(xs->det)) / xs->abc[0];
	if (xs->t[0] > 0 && xs->t[0] < xs->t[1])
		return (xs->t[0]);
	if (xs->t[1] > 0)
	{
		if (xs->t[0] < xs->t[1])
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
	else if (xs->type == CENTER_SIDE_HIT)
		return (cylinder1(cy, xs));
	else if (xs->type == CENTER_CENTER_HIT)
		return (cylinder2(cy, xs));
	else if (xs->type == SIDE_SIDE_HIT)
		return (cylinder3(cy, xs));
	else
		return (cylinder4(cy, xs));
}

double	intersect_cone(t_fig *cn, t_xs *xs)
{
	if (fabs(xs->abc[0]) < EPSILON \
		&& abs(xs->abc[1] < EPSILON))
		return (parallel_to_cn_norm(cn, xs));
	if (xs->det < 0)
		return (-1.0);
	get_cn_solution(cn, xs);
	// return (EPSILON);
	if (xs->type == NO_HIT)
		return (-1.0);
	if (xs->type == SIDE_SIDE_HIT)
	{
		// return (EPSILON);
		if (xs->t[0] > 0)
			return (xs->t[0]);
		if (xs->t[1] > 0)
			return (xs->t[1]);
		return (-1.0);
	}
	else if (xs->type == CENTER_SIDE_HIT)
	{
		// return (EPSILON);
		t_vector	top;
		
		top = add_vec(cn->xyz, mul_vec(cn->normal_vec, xs->h));
		if (xs->left >= xs->c && xs->right >= xs->c)
			return (xs->t[1]);
		if (xs->alpha < 0)
			return (cone1(cn, xs, cn->xyz));
		return (cone1(cn, xs, top));
	}
	else if (xs->type == SIDE_CENTER_HIT)
	{
		// return (EPSILON);
		t_vector	top;
		
		top = add_vec(cn->xyz, mul_vec(cn->normal_vec, xs->h));
		if (xs->left >= xs->c && xs->right >= xs->c)
			return (xs->t[1]);
		if (xs->alpha > xs->h)
			return (cone1(cn, xs, top));
		return (cone1(cn, xs, cn->xyz));
	}
	else
	{
		// return (EPSILON);
		t_vector	top;
		
		top = add_vec(cn->xyz, mul_vec(cn->normal_vec, xs->h));
		if (xs->t[1] < 0)
		{
			if (xs->left >= xs->c && xs->right >= xs->c)
			{
				if (xs->beta < 0)
					return (cone1(cn, xs, cn->xyz));
				return (cone1(cn, xs, top));
			}
			return (-1.0);
		}
		else if (xs->t[0] < 0)
		{
			if (xs->beta >= 0 && xs->beta <= xs->h)
				return (xs->t[1]);
			return (-1.0);
		}
		else
		{
			// return (EPSILON);
			if (xs->left >= xs->c && xs->right >= xs->c)
			{
				if (xs->alpha >= 0 && xs->alpha <= xs->h)
					return (xs->t[0]);
				return (-1.0);
			}
			// return (-1.0);
			if (xs->alpha < cn->height)
				return (cone1(cn, xs, cn->xyz));
			return (-1.0);
			return (cone1(cn, xs, cn->xyz));
		}
	}

	// if (xs->t[0] > 0)
	// {
	// 	if (xs->alpha <= xs->h && xs->alpha >= 0)
	// 		return (xs->t[0]);
	// 	if (xs->beta >= 0 && xs->beta <= xs->h)
	// 		return (xs->t[1]);
	// 	return (-1.0);
	// }
	// else
	// {
	// 	double	d;
	// 	double	e;
	// 	double	f;

	// 	d = dot_product(xs->ray_dir, sub_vec(cn->xyz, xs->from));
	// 	e = dot_product(xs->ray_dir, sub_vec(add_vec(cn->xyz, \
	// 		mul_vec(cn->normal_vec, 2 * cn->height)), xs->from));
	// 	f = xs->dn / sqrt(dot_product(xs->ray_dir, xs->ray_dir));
	// 	if (xs->t[1] > 0)
	// 	{
	// 		if (xs->beta <= xs->h && xs->beta >= 0)
	// 			return (xs->t[1]);
	// 		if (xs->alpha > 0 && xs->beta < 0 \
	// 			&& fabs(f) <= xs->c && d >= 0 && e < 0)
	// 			return (cone1(cn, xs, cn->xyz));
	// 		if (xs->alpha < xs->h && xs->beta > xs->h \
	// 			&& fabs(f) <= xs->c && e >= 0 && d < 0)
	// 			return (cone1(cn, xs, add_vec(cn->xyz, \
	// 				mul_vec(cn->normal_vec, 2 * cn->height))));
	// 	}
	// 	else
	// 	{
	// 		if (fabs(f) >= xs->c && d >= 0 && e < 0)
	// 			return (cone1(cn, xs, cn->xyz));
	// 		if (fabs(f) >= xs->c && e >= 0 && d < 0)
	// 			return (cone1(cn, xs, add_vec(cn->xyz, \
	// 				mul_vec(cn->normal_vec, 2 * cn->height))));
	// 	}
	// }
	// return (-1.0);
}
