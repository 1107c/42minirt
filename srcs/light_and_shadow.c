/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  light_and_shadow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 23:47:18 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	add_color(t_color *color, t_fig *fig, t_vec *vec, t_light *tmp)
{
	color->diffuse_color = mul_vec((t_vector){fmin(255, fmax(0, fig->rgb.x \
	* tmp->rgb.x)), fmin(255, fmax(0, fig->rgb.y * tmp->rgb.y)), fmin(255, \
	fmax(0, fig->rgb.z * tmp->rgb.z)), 0}, fmax(0.0, dot_product(vec->n_vec, \
	vec->l_vec)) * tmp->brightness * DIFFUSE_STRENGTH);
	color->specular_color = mul_vec(tmp->rgb, pow(fmax(0.0, \
	dot_product(vec->e_vec, vec->r_vec)), SHINESS) * \
	tmp->brightness * SPECULAR_STRENGTH);
	color->dif_sum = add_vec(color->dif_sum, color->diffuse_color);
	color->spe_sum = add_vec(color->spe_sum, color->specular_color);
}

int	is_in_shadow(t_rt *rt, t_vector inter_vec, t_vector light_dir, \
	t_light *light)
{
	t_fig	*fig;
	double	t;
	double	max_t;
	int		flg;

	fig = rt->fig;
	max_t = sqrt(dot_product ((sub_vec(light->xyz, inter_vec)), \
		sub_vec(light->xyz, inter_vec)));
	while (fig)
	{
		flg = 0;
		if (fig->type == PLANE)
			t = intersect_plane(fig, inter_vec, add_vec(inter_vec, light_dir));
		else if (fig->type == SPHERE)
			t = intersect_sphere(fig, inter_vec, add_vec(inter_vec, light_dir));
		else if (fig->type == CYLINDER)
			t = intersect_cylinder(fig, inter_vec, add_vec(inter_vec, \
				light_dir), &flg);
		else if (fig->type == CONE)
			t = intersect_cone(fig, inter_vec, add_vec(inter_vec, light_dir));
		if (t > 0.001 && t < max_t)
			return (1);
		fig = fig->next;
	}
	return (0);
}

void	multi_lightning(t_rt *rt, t_vec *vec, t_color *c, t_fig *fig)
{
	t_light	*tmp;

	c->dif_sum = (t_vector){0, 0, 0, 0};
	c->spe_sum = (t_vector){0, 0, 0, 0};
	vec->e_vec = normalize_vec(sub_vec(rt->cam->coords, vec->inter_vec));
	tmp = rt->light;
	while (tmp)
	{
		vec->l_vec = normalize_vec(sub_vec(tmp->xyz, vec->inter_vec));
		vec->r_vec = (normalize_vec(sub_vec(mul_vec(vec->n_vec, 2 * \
			dot_product(vec->n_vec, vec->l_vec)), vec->l_vec)));
		if (!is_in_shadow(rt, vec->inter_vec, vec->l_vec, tmp))
			add_color(c, fig, vec, tmp);
		c->specular_color = mul_vec(tmp->rgb, pow(fmax(0.0, \
			dot_product(vec->e_vec, vec->r_vec)), SHINESS) \
		* tmp->brightness * SPECULAR_STRENGTH);
		c->spe_sum = add_vec(c->spe_sum, c->specular_color);
		tmp = tmp->next;
	}
	c->amb = mul_vec(fig->rgb, rt->amblight->light_ratio * AMBIENT_STRENGTH);
	c->final_color.x = fmin(255, c->amb.x + c->dif_sum.x + c->spe_sum.x);
	c->final_color.y = fmin(255, c->amb.y + c->dif_sum.y + c->spe_sum.y);
	c->final_color.z = fmin(255, c->amb.z + c->dif_sum.z + c->spe_sum.z);
}
