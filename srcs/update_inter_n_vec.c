/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_inter_n_vec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 23:47:18 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	update_closest_cylinder(t_util *util, t_fig *fig)
{
	double	theta;

	if (util->xs.flag == 1)
		util->vec.n_vec = fig->normal_vec;
	else if (util->xs.flag == 2)
		util->vec.n_vec = invert_vec(fig->normal_vec);
	else if (util->xs.flag == 3)
		util->vec.n_vec = init_vector(0, 0, 0);
	else
	{
		util->vec.n_vec = sub_vec(util->vec.inter_vec, fig->xyz);
		theta = dot_product(util->vec.n_vec, fig->normal_vec) / \
			sqrt(dot_product(util->vec.n_vec, util->vec.n_vec));
		util->vec.n_vec = sub_vec(util->vec.n_vec, \
			mul_vec(fig->normal_vec, theta));
		util->vec.n_vec = normalize_vec(util->vec.n_vec);
	}
}

void	update_closest_figure(t_util *util, t_fig *fig, \
								t_vector to, double time)
{
	util->time = time;
	util->vec.fig = fig;
	util->vec.inter_vec = add_vec(util->xs.from, \
							mul_vec(util->xs.ray_dir, time));
	if (fig->type == PLANE)
		util->vec.n_vec = fig->normal_vec;
	else if (fig->type == SPHERE)
	{
		if (!util->xs.flag)
			util->vec.n_vec = normalize_vec(sub_vec(util->vec.inter_vec, \
				fig->xyz));
		else
			util->vec.n_vec = init_vector(0, 0, 0);
	}
	else if (fig->type == CYLINDER)
		update_closest_cylinder(util, fig);
	else
		util->vec.n_vec = get_cone_normal(fig, \
							util->xs.from, to, time);
}
