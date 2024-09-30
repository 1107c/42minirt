/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:21:50 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/09 15:13:57 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	add_vec(t_vector lhs, t_vector rhs)
{
	return ((t_vector){lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, NULL});
}

t_vector	sub_vec(t_vector lhs, t_vector rhs)
{
	return ((t_vector){lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, NULL});
}

t_vector	mul_vec(t_vector lhs, double rhs)
{
	return ((t_vector){lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, NULL});
}

int	is_normalized_vec(t_vector vec)
{
	double	d;

	d = sqrt(dot_product(vec, vec));
	if (d >= 0.999 && d <= 1.001)
		return (1);
	return (0);
}

t_vector	init_point(t_cam *cam)
{
	t_vector	vec;

	vec = add_vec(cam->coords, mul_vec(cam->orient_vec, cam->distance_to_view));
	vec = sub_vec(vec, mul_vec(cam->right_vec, WINDOW_WIDTH / 2));
	vec = add_vec(vec, mul_vec(cam->up_vec, WINDOW_HEIGHT / 2));
	return (vec);
}
