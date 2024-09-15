/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:11:44 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/15 17:11:44 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_plane(t_rt *rt, t_vec	t1)
{
	t_vec	eye_start;
	t_vec	eye_ray;
	int	ret;
	t_plane	tp;

	tp = rt->obj->u_obj.plane;
	eye_start = rt->cam.coords_vec;
	eye_ray = sub_vec(t1, eye_start);

	if (dot_product(tp.orient_vec, eye_ray) == 0)
	{
		if(dot_product(tp.orient_vec, sub_vec(tp.coords_vec, eye_start)) == 0)
			return (1);
		else
			return (0);
	}

	ret = dot_product(tp.orient_vec, sub_vec(tp.coords_vec, eye_start)) / dot_product(tp.orient_vec, eye_ray);

	return (ret);
}

draw_plane()
{
	if (inter() > 0)

}
