/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_inter_n_vec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:58:48 by ksuh              #+#    #+#             */
/*   Updated: 2024/10/01 15:58:48 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_vector	update_closest_cylinder(t_util *util, t_fig *fig);

void	update_closest_figure(t_util *util, t_fig *fig, double time)
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
		util->vec.n_vec = update_closest_cylinder(util, fig);
	else
		util->vec.n_vec = get_cone_normal(fig, &util->xs, time);
}

t_vector	update_closest_cylinder(t_util *util, t_fig *fig)
{
	t_vector	n_vec;
	double		theta;

	if (util->xs.flag == 1)
		return (fig->normal_vec);
	else if (util->xs.flag == 2)
		return (invert_vec(fig->normal_vec));
	else if (util->xs.flag == 3)
		return (init_vector(0, 0, 0));
	else
	{
		n_vec = sub_vec(util->vec.inter_vec, fig->xyz);
		theta = dot_product(n_vec, fig->normal_vec) / \
			sqrt(dot_product(n_vec, n_vec));
		n_vec = sub_vec(n_vec, \
			mul_vec(fig->normal_vec, theta));
		return (normalize_vec(n_vec));
	}
}
