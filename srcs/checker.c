/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:39:01 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/28 17:39:01 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int		is_checker(double u, double v, int checker_size);
static t_vector	get_final_color(t_color *color, int add);

void	checkerboard(t_vector point, t_vec *vec, t_color *color)
{
	double	uv[2];

	if (vec->fig->type == PLANE)
		get_plane_uv(uv, vec->inter_vec, vec->fig);
	else if (vec->fig->type == SPHERE)
		get_sphere_uv(uv, vec->n_vec);
	else if (vec->fig->type == CYLINDER || vec->fig->type == CONE)
		get_cylinder_uv(uv, vec->inter_vec, vec->fig);
	if (is_checker(uv[0], uv[1], 10))
		color->final_color = get_final_color(color, 0);
	else
		color->final_color = get_final_color(color, 255);
}

int	is_checker(double u, double v, int checker_size)
{
	int	u_check;
	int	v_check;

	if (u < 0)
		u = -u + 0.1;
	if (v < 0)
		v = -v + 0.1;
	u_check = (int)(u * checker_size);
	v_check = (int)(v * checker_size);
	return ((u_check + v_check) % 2);
}

t_vector	get_final_color(t_color *color, int add)
{
	double	x;
	double	y;
	double	z;

	x = fmin(255, color->spe_sum.x + add);
	y = fmin(255, color->spe_sum.y + add);
	z = fmin(255, color->spe_sum.z + add);
	return (init_vector(x, y, z));
}
