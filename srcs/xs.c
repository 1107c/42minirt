/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 20:10:37 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/29 20:10:37 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	plane_xs(t_fig *pl, t_xs *xs)
{
	xs->left = dot_product(pl->normal_vec, xs->ray_dir);
	xs->right = dot_product(pl->normal_vec, pl->xyz) \
			- dot_product(pl->normal_vec, xs->from);
}

void	sphere_xs(t_fig *sp, t_xs *xs)
{
	xs->from_fig_center = sub_vec(xs->from, sp->xyz);
	xs->abc[0] = dot_product(xs->ray_dir, xs->ray_dir);
	xs->abc[1] = dot_product(xs->ray_dir, xs->from_fig_center);
	xs->abc[2] = dot_product(xs->from_fig_center, \
				xs->from_fig_center) - sp->radius_sq;
	xs->det = pow(xs->abc[1], 2) - xs->abc[0] * xs->abc[2];
	xs->flag = 0;
}

void	cylinder_xs(t_fig *cy, t_xs *xs)
{
	xs->from_fig_center = sub_vec(xs->from, cy->xyz);
	xs->dn = dot_product(xs->ray_dir, cy->normal_vec);
	xs->ecn = dot_product(xs->from_fig_center, cy->normal_vec);
	xs->abc[0] = dot_product(xs->ray_dir, xs->ray_dir) \
				- pow(xs->dn, 2);
	xs->abc[1] = dot_product(xs->ray_dir, xs->from_fig_center) \
				- xs->ecn * xs->dn;
	xs->abc[2] = dot_product(xs->from_fig_center, xs->from_fig_center) \
				- pow(xs->ecn, 2) - cy->radius_sq;
	xs->det = pow(xs->abc[1], 2) - xs->abc[0] * xs->abc[2];
	xs->h = cy->height;
	xs->flag = 0;
}

void	cone_xs(t_fig *cn, t_xs *xs)
{
	double	h_ratio;
	double	radius;

	xs->from_fig_center = sub_vec(xs->from, cn->xyz);
	xs->dn = dot_product(xs->ray_dir, cn->normal_vec);
	xs->ecn = dot_product(xs->from_fig_center, cn->normal_vec);
	xs->ecd = dot_product(xs->ray_dir, xs->from_fig_center);
	radius = cn->diameter / 2;
	h_ratio = pow(radius / cn->height, 2);
	xs->abc[0] = dot_product(xs->ray_dir, xs->ray_dir) \
				- (1 + h_ratio) * pow(xs->dn, 2);
	xs->abc[1] = xs->ecd - xs->ecn * xs->dn * (1 + h_ratio) \
				+ h_ratio * cn->height * xs->dn;
	xs->abc[2] = dot_product(xs->from_fig_center, xs->from_fig_center) \
				+ 2 * (cn->radius_sq / cn->height) * xs->ecn \
				- (1 + h_ratio) * pow(xs->ecn, 2) - cn->radius_sq;
	xs->c = cn->height / sqrt(cn->radius_sq + pow(cn->height, 2));
	xs->h = cn->height * 2;
	xs->det = pow(xs->abc[1], 2) - xs->abc[0] * xs->abc[2];
	xs->flag = 0;
}
