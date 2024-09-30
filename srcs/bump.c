/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:53:00 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/28 17:53:00 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	boundary_check(int tmp, double max)
{
	if (tmp < 0)
	{
		while (tmp < max)
			tmp += max;
		if (tmp < max / 10000)
			tmp += max * 0.9999;
		else if (tmp > max - (max / 10000))
			tmp -= max * 0.9999;
	}
	else if (tmp >= max)
	{
		while (tmp >= max)
			tmp -= max;
	}
	return (tmp);
}

void	get_bump_uv(t_vec *vec, int *u, int *v, double *uv)
{
	if (vec->fig->bump->normal_width > vec->fig->bump->normal_height)
		vec->fig->bump->normal_width = vec->fig->bump->normal_height;
	else
		vec->fig->bump->normal_height = vec->fig->bump->normal_width;
	*u = (uv[0] * (vec->fig->bump->normal_width - 1));
	*v = (uv[1] * (vec->fig->bump->normal_height - 1));
}

t_vector	update_nvec(t_vec *vec, t_vector normal_from_map)
{
	t_vector	y_unit_vector;
	t_vector	tangent;
	t_vector	bitangent;
	t_vector	new_normal;

	if (fabs(vec->n_vec.y) != 1)
		y_unit_vector = (t_vector){0, 1, 0, 0};
	else
		y_unit_vector = (t_vector){0, 0, -vec->n_vec.y, 0};
	tangent = normalize_vec(cross_product(y_unit_vector, vec->n_vec));
	bitangent = normalize_vec(cross_product(vec->n_vec, tangent));
	new_normal.x = tangent.x * normal_from_map.x + bitangent.x * \
		normal_from_map.y + vec->n_vec.x * normal_from_map.z;
	new_normal.y = tangent.y * normal_from_map.x + bitangent.y * \
		normal_from_map.y + vec->n_vec.y * normal_from_map.z;
	new_normal.z = tangent.z * normal_from_map.x + bitangent.z * \
		normal_from_map.y + vec->n_vec.z * normal_from_map.z;
	return (new_normal);
}

void	bump(t_worker *wk, t_vec *vec, t_color *color)
{
	double		uv[2];
	int			u;
	int			v;
	t_vector	normal_from_map;
	t_vector	color_from_map;

	get_uv(vec, uv);
	u = 0;
	v = 0;
	get_bump_uv(vec, &u, &v, uv);
	u = boundary_check(u, vec->fig->bump->normal_width);
	v = boundary_check(v, vec->fig->bump->normal_height);
	normal_from_map = vec->fig->bump->normal_map[v][u];
	color_from_map = vec->fig->bump->color_map[v][u];
	vec->n_vec = update_nvec(vec, normal_from_map);
	multi_lightning(wk->rt->light, wk->rt->fig, &wk->util, wk->rt->amblight);
	color->final_color = color_from_map;
}
