/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figure.c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:16:37 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 15:17:16 by ksuh             ###   ########.fr       */
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


// void	parse_fig(t_fig *fig, t_rt *rt, char **args, char **tmp)
// {
// 	fig_check(fig, rt, args, tmp);
// 	if (fig->type == 1 || fig->type == 2)
// 	{
// 		is_valid_multi_double_value(fig->xyz, args[0], INT_MIN, INT_MAX);
// 		tmp = split_comma(rt, 2, args);
// 		fig->vx = ft_atod(tmp[0]);
// 		fig->vy = ft_atod(tmp[1]);
// 		fig->vz = ft_atod(tmp[2]);
// 		if (!is_double_range(fig->vx, -1.0, 1.0) || !is_double_range(fig->\
// 		vy, -1.0, 1.0) || !is_double_range(fig->vz, -1.0, 1.0))
// 		{
// 			free_args(tmp);
// 			free_2d_and_close_all(rt, args, FORMAT_ERR);
// 		}
// 		free_args(tmp);
// 		if (fig->type == 2)
// 		{
// 			fig->diameter = ft_atod(args[3]);
// 			fig->height = ft_atod(args[4]);
// 		}
// 	}
// 	if (fig->type == 0)
// 		fig->diameter = ft_atod(args[2]);
// }

// void	fig_check(int max, t_rt *rt, char **args, char **tmp)
// {
// 	int	max;

// 	max = 4;
// 	if (fig->type == 2)
// 		max = 6;
// 	if (get_arg_len(args) != max)
// 		free_2d_and_close_all(rt, args, AMB_LEN_ERR);
// 	if (fig->type == 0)
// 		if (ft_strchr(args[2], ','))
// 			free_2d_and_close_all(rt, args, AMB_RATIO_FORMAT_ERR);
// 	if (fig->type == 2)
// 		if (ft_strchr(args[3], ',') || ft_strchr(args[4], ','))
// 			free_2d_and_close_all(rt, args, AMB_RATIO_FORMAT_ERR);
// 	tmp = split_comma(rt, 1, args);
// 	fig->x = ft_atod(tmp[0]);
// 	fig->y = ft_atod(tmp[1]);
// 	fig->z = ft_atod(tmp[2]);
// 	free_args(tmp);
// 	tmp = split_comma(rt, max - 1, args);
// 	if (!is_valid_int_range(arr, 0, 255))
// 		free_2d_and_close_all(rt, tmp, AMB_RGB_RANGE_ERR);
// 	fig->r = ft_atol(tmp[0]);
// 	fig->g = ft_atol(tmp[1]);
// 	fig->b = ft_atol(tmp[2]);
// 	free_args(tmp);
// }

// char**	split_comma(t_rt *rt, int num, char **args)
// {
// 	char	**res;

// 	res = ft_split(args[num], ft_iscomma);
// 	if (!res)
// 		free_2d_and_close_all(rt, args, MEM_ALLOC_ERR);
// 	if (get_arg_len(res) != 3)
// 	{
// 		free_args(res);
// 		free_2d_and_close_all(rt, args, FORMAT_ERR);
// 	}
// 	return (res);
// }