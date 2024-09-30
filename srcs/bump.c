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

void    bump(t_rt *rt, t_vector point, t_vec *vec, t_color *color)
{
	double  uv[2];
    t_vector normal_from_map;
    t_vector color_from_map;
    t_vector tangent, bitangent;
    t_vector new_normal;

    if (vec->fig->type == SPHERE)
        get_sphere_uv(uv, vec->n_vec);
    else if (vec->fig->type == PLANE)
        get_plane_uv(uv, vec->inter_vec, vec->fig);
    else if (vec->fig->type == CYLINDER || vec->fig->type == CONE)
        get_cylinder_uv(uv, vec->inter_vec, vec->fig);
    if (vec->fig->bump->normal_width > vec->fig->bump->normal_height)
    	vec->fig->bump->normal_width = vec->fig->bump->normal_height;
    else
     	vec->fig->bump->normal_height = vec->fig->bump->normal_width;
    int u = (uv[0] * (vec->fig->bump->normal_width - 1));
    int v = (uv[1] * (vec->fig->bump->normal_height - 1));
   	if (u < 0)
    	{
	     	while (u < vec->fig->bump->normal_width)
				u += vec->fig->bump->normal_width;
					if (u < vec->fig->bump->normal_height / 10000)
						u += vec->fig->bump->normal_width* 0.9999 ;
					else if (u > vec->fig->bump->normal_width - vec->fig->bump->normal_width / 10000)
						u -= vec->fig->bump->normal_width* 0.9999 ;
     	}
		else if (u >= vec->fig->bump->normal_width)
		{
			while (u >= vec->fig->bump->normal_width)
				u -= vec->fig->bump->normal_width;

		}
   	if (v < 0)
    	{
	     	while (v < 0)
				v += vec->fig->bump->normal_height;
				if (v < vec->fig->bump->normal_height / 10000)
					v += vec->fig->bump->normal_height* 0.9999 ;
					else if (v > vec->fig->bump->normal_height - vec->fig->bump->normal_height / 10000)
						v -= vec->fig->bump->normal_height* 0.9999 ;
     	}
		else if (v >= vec->fig->bump->normal_height)
		{
			while (v >= vec->fig->bump->normal_height)
					v -= vec->fig->bump->normal_height;

		}
	    normal_from_map = vec->fig->bump->normal_map[v][u];
		color_from_map = vec->fig->bump->color_map[v][u];

	    t_vector	y_unit_vector;
	    if (fabs(vec->n_vec.y) != 1)
			y_unit_vector = (t_vector){0, 1, 0, 0};
		else
			y_unit_vector = (t_vector){0, 0, -vec->n_vec.y, 0};
		tangent = normalize_vec(cross_product(y_unit_vector, vec->n_vec));
		bitangent = normalize_vec(cross_product( vec->n_vec , tangent));
	    new_normal.x = tangent.x * normal_from_map.x + bitangent.x * normal_from_map.y + vec->n_vec.x * normal_from_map.z;
	    new_normal.y = tangent.y * normal_from_map.x + bitangent.y * normal_from_map.y + vec->n_vec.y * normal_from_map.z;
	    new_normal.z = tangent.z * normal_from_map.x + bitangent.z * normal_from_map.y + vec->n_vec.z * normal_from_map.z;
	    new_normal = normalize_vec(new_normal);

	    vec->n_vec = new_normal;

	    multi_lightning(rt, vec, color, vec->fig);
	    color->final_color = color_from_map;
}