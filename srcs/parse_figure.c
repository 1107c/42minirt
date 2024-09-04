/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:16:37 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 17:18:09 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	parse_plane(t_rt *rt, char **args)
{
	t_fig	*fig;

	fig = lst_back(rt, FIG);
	if (!fig)
		free_2d_and_close_all(rt, args, MEM_ALLOC_ERR);
	if (get_arg_len(args) != 4)
		free_2d_and_close_all(rt, args, AMB_LEN_ERR);
	if (!is_valid_multi_double_value(fig->xyz, args[1], INT_MIN, INT_MAX))
		free_2d_and_close_all(rt, args, fig->xyz->error);
	if (!is_valid_multi_double_value(fig->normal_vec, args[2], -1, 1))
		free_2d_and_close_all(rt, args, fig->normal_vec->error);
	if (!is_valid_multi_double_value(fig->rgb, args[3], 0, 255))
		free_2d_and_close_all(rt, args, fig->rgb->error);
}

void	parse_sphere(t_rt *rt, char **args)
{
	t_fig	*fig;

	fig = lst_back(rt, FIG);
	if (!fig)
		free_2d_and_close_all(rt, args, MEM_ALLOC_ERR);
	fig->type = SPHERE;
	if (get_arg_len(args) != 4)
		free_2d_and_close_all(rt, args, AMB_LEN_ERR);
	if (!is_valid_multi_double_value(fig->xyz, args[1], INT_MIN, INT_MAX))
		free_2d_and_close_all(rt, args, fig->xyz->error);
	if (!is_valid_single_double_value(rt, args[2], 0, INT_MAX))
		free_2d_and_close_all(rt, args, rt->error);
	fig->diameter = ft_atod(args[2]);
	if (!is_valid_multi_double_value(fig->rgb, args[3], 0, 255))
		free_2d_and_close_all(rt, args, fig->rgb->error);
}

void	parse_cylinder(t_rt *rt, char **args)
{
	t_fig	*fig;

	fig = lst_back(rt, FIG);
	if (!fig)
		free_2d_and_close_all(rt, args, MEM_ALLOC_ERR);
	fig->type = CYLINDER;
	if (get_arg_len(args) != 6)
		free_2d_and_close_all(rt, args, AMB_LEN_ERR);
	if (!is_valid_multi_double_value(fig->xyz, args[1], INT_MIN, INT_MAX))
		free_2d_and_close_all(rt, args, fig->xyz->error);
	if (!is_valid_multi_double_value(fig->normal_vec, args[2], -1, 1))
		free_2d_and_close_all(rt, args, fig->normal_vec->error);
	if (!is_valid_single_double_value(rt, args[3], 0, INT_MAX))
		free_2d_and_close_all(rt, args, rt->error);
	fig->diameter = ft_atod(args[3]);
	if (!is_valid_single_double_value(rt, args[4], 0, INT_MAX))
		free_2d_and_close_all(rt, args, rt->error);
	fig->height = ft_atod(args[4]);
	if (!is_valid_multi_double_value(fig->rgb, args[5], 0, 255))
		free_2d_and_close_all(rt, args, fig->rgb->error);
}
