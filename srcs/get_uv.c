/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 23:47:18 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	get_plane_uv(double uv[2], t_vector inter_vec, t_fig *fig)
{
	t_vector	tmp;
	double		u2[2];
	double		v2[2];
	double		det;

	u2[0] = fig->right_vec.x;
	u2[1] = fig->right_vec.y;
	v2[0] = fig->up_vec.x;
	v2[1] = fig->up_vec.y;
	tmp = sub_vec(inter_vec, fig->xyz);
	if (fig->right_vec.x == 0 && fig->up_vec.x == 0)
	{
		u2[0] = fig->right_vec.z;
		v2[0] = fig->up_vec.z;
		tmp.x = tmp.z;
	}
	else if (fig->right_vec.y == 0 && fig->up_vec.y == 0)
	{
		u2[1] = fig->right_vec.z;
		v2[1] = fig->up_vec.z;
		tmp.y = tmp.z;
	}
	det = u2[0] * v2[1] - u2[1] * v2[0];
	uv[0] = 0.05 * (v2[1] * tmp.x - v2[0] * tmp.y) / det;
	uv[1] = 0.05 * (-u2[1] * tmp.x - u2[0] * tmp.y) / det;
}

void	get_sphere_uv(double uv[2], t_vector point)
{
	uv[0] = 0.5 + (atan2(point.z, point.x)) / (2 * M_PI);
	uv[1] = 0.5 + asin(point.y) / M_PI;
}

void	get_cylinder_uv(double uv[2], t_vector point, t_fig *fig)
{
	t_vector	pc;
	double		theta;
	double		height;

	pc = normalize_vec(sub_vec(point, add_vec(fig->xyz, \
		mul_vec(fig->normal_vec, fig->height / 2))));
	theta = atan2(dot_product(pc, fig->right_vec), \
			dot_product(pc, fig->up_vec)) + M_PI;
	height = dot_product(pc, fig->normal_vec);
	uv[0] = (theta * (0.5 * M_PI));
	uv[1] = fmod(height, 1);
}
