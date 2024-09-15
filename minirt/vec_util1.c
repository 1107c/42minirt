/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_util1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:00:55 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/15 18:00:55 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot_product(t_vec lhs, t_vec rhs)
{
	return (lhs.x * rhs.x + lhs.y * lhs.y + lhs.z * rhs.z);
}

t_vec	cross_product(t_vec lhs, t_vec rhs)
{
	return ((t_vec) {lhs.y * rhs.z - lhs.z * rhs.y, \
	lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x});
}

t_vec	normalize_vec(t_vec rhs)
{
	double	l;

	l = sqrt(dot_product(rhs, rhs));
	if (l == 0)
		return ((t_vec){0, 0, 0});
	else
		return ((t_vec){rhs.x / l, rhs.y / l, rhs.z / l});
}

t_vec	add_vec(t_vec lhs, t_vec rhs)
{
	return ((t_vec){lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z});
}

t_vec	sub_vec(t_vec lhs, t_vec rhs)
{
	return ((t_vec){lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z});
}
