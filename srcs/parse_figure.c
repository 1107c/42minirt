/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:16:37 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/05 09:37:58 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_fig	*get_figure(t_rt *rt, char **args, int len, int type);

void	parse_plane(t_rt *rt, char **args, int type)
{
	t_fig	*fig;

	fig = get_figure(rt, args, 4, type);
	if (!is_valid_multi_double_value(&(fig->xyz), args[1], INT_MIN, INT_MAX))
		free_2d_and_close_all(rt, args, fig->xyz.error);
	if (!is_valid_multi_double_value(&(fig->normal_vec), args[2], -1, 1))
		free_2d_and_close_all(rt, args, fig->normal_vec.error);
	if (!is_normalized_vec(rt->fig->normal_vec))
		free_2d_and_close_all(rt, args, NORM_VEC_ERR);
	if (!is_valid_multi_double_value(&(fig->rgb), args[3], 0, 255))
		free_2d_and_close_all(rt, args, fig->rgb.error);
}

void	parse_sphere(t_rt *rt, char **args, int type)
{
	t_fig	*fig;

	fig = get_figure(rt, args, 4, type);
	if (!is_valid_multi_double_value(&(fig->xyz), args[1], INT_MIN, INT_MAX))
		free_2d_and_close_all(rt, args, fig->xyz.error);
	if (!is_valid_single_double_value(rt, args[2], EPSILON, INT_MAX))
		free_2d_and_close_all(rt, args, rt->error);
	fig->diameter = ft_atod(args[2]);
	fig->radius_sq = pow(fig->diameter / 2, 2);
	if (!is_valid_multi_double_value(&(fig->rgb), args[3], 0, 255))
		free_2d_and_close_all(rt, args, fig->rgb.error);
}

void	parse_cylinder(t_rt *rt, char **args, int type)
{
	t_fig	*fig;

	fig = get_figure(rt, args, 6, type);
	if (!is_valid_multi_double_value(&(fig->xyz), args[1], INT_MIN, INT_MAX))
		free_2d_and_close_all(rt, args, fig->xyz.error);
	if (!is_valid_multi_double_value(&(fig->normal_vec), args[2], -1, 1))
		free_2d_and_close_all(rt, args, fig->normal_vec.error);
	if (!is_normalized_vec(rt->fig->normal_vec))
		free_2d_and_close_all(rt, args, NORM_VEC_ERR);
	if (!is_valid_single_double_value(rt, args[3], EPSILON, INT_MAX))
		free_2d_and_close_all(rt, args, rt->error);
	fig->diameter = ft_atod(args[3]);
	fig->radius_sq = pow(fig->diameter / 2, 2);
	if (!is_valid_single_double_value(rt, args[4], EPSILON, INT_MAX))
		free_2d_and_close_all(rt, args, rt->error);
	fig->height = ft_atod(args[4]);
	if (!is_valid_multi_double_value(&(fig->rgb), args[5], 0, 255))
		free_2d_and_close_all(rt, args, fig->rgb.error);
}

t_fig	*get_figure(t_rt *rt, char **args, int len, int type)
{
	t_fig	*fig;

	if (rt->fig_cnt == FIG_MAX)
		free_2d_and_close_all(rt, args, FIG_MAX_ERR);
	fig = lst_addback(rt, FIG);
	if (!fig)
		free_2d_and_close_all(rt, args, MEM_ALLOC_ERR);
	fig->type = type;
	if (get_arg_len(args) != len)
		free_2d_and_close_all(rt, args, FIG_LEN_ERR);
	return (fig);
}
