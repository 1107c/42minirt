/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lihgt_and_shadow_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 06:21:04 by myeochoi          #+#    #+#             */
/*   Updated: 2024/09/16 06:30:28 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	get_diffuse_color(t_light *lt, t_fig *fig, double power)
{
	t_vector	diffuse;
	double		xyz[3];

	xyz[0] = fmin(255, fmax(0, fig->rgb.x * lt->rgb.x));
	xyz[1] = fmin(255, fmax(0, fig->rgb.y * lt->rgb.y));
	xyz[2] = fmin(255, fmax(0, fig->rgb.z * lt->rgb.z));
	diffuse = init_vector(xyz[0], xyz[1], xyz[2]);
	diffuse = mul_vec(diffuse, fmax(0.0, power) \
			* lt->brightness * DIFFUSE_STRENGTH);
	return (diffuse);
}

t_vector	get_specular_color(t_light *lt, double power)
{
	double	total_power;

	total_power = pow(fmax(0.0, power), SHINESS) \
					* lt->brightness * SPECULAR_STRENGTH;
	return (mul_vec(lt->rgb, total_power));
}

t_vector	get_light_color(t_vector l_sum, t_light *lt, double power)
{
	double	xyz[3];

	xyz[0] = l_sum.x + power * lt->rgb.x * 0.2 * lt->brightness;
	xyz[1] = l_sum.y + power * lt->rgb.y * 0.2 * lt->brightness;
	xyz[2] = l_sum.z + power * lt->rgb.z * 0.2 * lt->brightness;
	xyz[0] = fmin(255, fmax(0, xyz[0]));
	xyz[1] = fmin(255, fmax(0, xyz[1]));
	xyz[2] = fmin(255, fmax(0, xyz[2]));
	return (init_vector(xyz[0], xyz[1], xyz[2]));
}

void	add_color(t_color *c, t_fig *fig, t_vec *vec, t_light *light)
{
	double	d_power;
	double	s_power;
	double	l_power;

	d_power = dot_product(vec->n_vec, vec->l_vec);
	if (fig->type == PLANE)
		d_power = fabs(d_power);
	s_power = dot_product(vec->e_vec, vec->r_vec);
	if (dot_product(vec->n_vec, vec->n_vec) == 0)
		s_power = 0;
	c->diffuse_color = get_diffuse_color(light, fig, d_power);
	c->specular_color = get_specular_color(light, s_power);
	c->dif_sum = add_vec(c->dif_sum, c->diffuse_color);
	c->spe_sum = add_vec(c->spe_sum, c->specular_color);
	l_power = dot_product(vec->l_vec, vec->r_vec);
	c->l_sum = get_light_color(c->l_sum, light, l_power);
}
