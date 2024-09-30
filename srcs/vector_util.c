/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:53:53 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/09 15:13:50 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	normalize_vec(t_vector rhs)
{
	double	l;

	l = sqrt(dot_product(rhs, rhs));
	if (l == 0)
		return ((t_vector){0, 0, 0, NULL});
	else
		return ((t_vector){rhs.x / l, rhs.y / l, rhs.z / l, NULL});
}

double	dot_product(t_vector lhs, t_vector rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

t_vector	cross_product(t_vector lhs, t_vector rhs)
{
	return ((t_vector){lhs.y * rhs.z - lhs.z * rhs.y, \
	lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x, NULL});
}

double	udistance_vec(t_vector lhs, t_vector rhs)
{
	double	dx;
	double	dy;
	double	dz;

	dx = lhs.x - rhs.x;
	dy = lhs.y - rhs.y;
	dz = lhs.z - rhs.z;
	return (sqrt(dx * dx + dy * dy + dz * dz));
}

t_vector	invert_vec(t_vector rhs)
{
	return ((t_vector){-rhs.x, -rhs.y, -rhs.z, NULL});
}
