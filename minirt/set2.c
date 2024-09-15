/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:25:57 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/14 13:25:57 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_plane(t_object *obj, char **tmp)
{
	t_plane	tp;

	ft_bzero(&tp, sizeof(t_plane));
	if (vec_parse(tmp[1], &tp.coords_vec))
		return (print_err(PSERR));
	if (normal_parse(tmp[2], &tp.orient_vec, -1.0, 1.0))
		return (print_err(PSERR));
	if (color_parse(&tp.rgb, tmp[3]))
		return (print_err(PSERR));
	obj->u_obj.plane = tp;
	return (0);
}

int	set_sphere(t_object *obj, char **tmp)
{
	t_sphere	ts;

	ft_bzero(&ts, sizeof(t_sphere));
	if (vec_parse(tmp[1], &ts.coords_vec))
		return (print_err(PSERR));
	ts.diameter = ft_stod(tmp[2]);
	if (ts.diameter <= 0.0)
		return (print_err(PSERR));
	if (color_parse(&ts.rgb, tmp[3]))
		return (print_err(PSERR));
	obj->u_obj.sphere = ts;
	return (0);
}

int	set_cylinder(t_object *obj, char **tmp)
{
	t_cylinder	tc;

	ft_bzero(&tc, sizeof(t_cylinder));
	if (vec_parse(tmp[1], &tc.coords_vec))
		return (print_err(PSERR));
	if (normal_parse(tmp[2], &tc.orient_vec, -1.0, 1.0))
		return (print_err(PSERR));
	tc.diameter = ft_stod(tmp[3]);
	if (tc.diameter <= 0.0)
		return (print_err(PSERR));
	tc.height = ft_stod(tmp[4]);
	if (tc.height <= 0.0)
		return (print_err(PSERR));
	if (color_parse(&tc.rgb, tmp[5]))
		return (print_err(PSERR));
	obj->u_obj.cylinder = tc;
	return (0);
}
