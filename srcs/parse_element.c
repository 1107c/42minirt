/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:27:14 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/16 06:33:01 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// ∗ identifier: A
// ∗ ambient lighting ratio in range [0.0,1.0]: 0.2
// ∗ R,G,B colors in range [0-255]: 255, 255, 255

void	parse_amb(t_rt *rt, char **args)
{
	if (rt->amblight->cnt)
		free_2d_and_close_all(rt, args, AMB_DUP_ERR);
	if (get_arg_len(args) != 3)
		free_2d_and_close_all(rt, args, AMB_LEN_ERR);
	if (!is_valid_single_double_value(rt, args[1], 0, 1))
		free_2d_and_close_all(rt, args, rt->error);
	rt->amblight->light_ratio = ft_atod(args[1]);
	if (!is_valid_multi_double_value(&(rt->amblight->rgb), args[2], 0, 255))
		free_2d_and_close_all(rt, args, rt->amblight->rgb.error);
	rt->amblight->cnt = 1;
}

void	parse_cam(t_rt *rt, char **args)
{
	if (rt->cam->cnt)
		free_2d_and_close_all(rt, args, CAM_DUP_ERR);
	if (get_arg_len(args) != 4)
		free_2d_and_close_all(rt, args, CAM_LEN_ERR);
	if (!is_valid_multi_double_value(&(rt->cam->coords), args[1], \
	INT_MIN, INT_MAX))
		free_2d_and_close_all(rt, args, rt->cam->coords.error);
	if (!is_valid_multi_double_value(&(rt->cam->orient_vec), args[2], -1, 1))
		free_2d_and_close_all(rt, args, rt->cam->orient_vec.error);
	if (!is_normalized_vec(rt->cam->orient_vec))
		free_2d_and_close_all(rt, args, NORM_VEC_ERR);
	if (!is_valid_single_double_value(rt, args[3], 0, 180))
		free_2d_and_close_all(rt, args, rt->error);
	rt->cam->fov = ft_atod(args[3]);
	rt->cam->cnt = 1;
}

void	parse_light(t_rt *rt, char **args)
{
	t_light	*light;

	if (rt->light_cnt == LIGHT_MAX)
		free_2d_and_close_all(rt, args, LIGHT_MAX_ERR);
	light = lst_addback(rt, LIGHT);
	if (!light)
		free_2d_and_close_all(rt, args, MEM_ALLOC_ERR);
	if (get_arg_len(args) != 4)
		free_2d_and_close_all(rt, args, LIGHT_LEN_ERR);
	if (!is_valid_multi_double_value(&(light->xyz), args[1], INT_MIN, INT_MAX))
		free_2d_and_close_all(rt, args, light->xyz.error);
	if (!is_valid_single_double_value(rt, args[2], 0, 1))
		free_2d_and_close_all(rt, args, rt->error);
	light->brightness = ft_atod(args[2]);
	if (!is_valid_multi_double_value(&(light->rgb), args[3], 0, 255))
		free_2d_and_close_all(rt, args, light->rgb.error);
}
