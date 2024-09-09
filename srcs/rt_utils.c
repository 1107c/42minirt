/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:26:32 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 17:45:07 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	print_amblight(t_amblight *amb);
static void	print_camera(t_cam *cam);
static void	print_light(t_light *light);
static void	print_fig(t_fig *fig);

void	print_rt(t_rt *rt)
{
	print_amblight(rt->amblight);
	print_camera(rt->cam);
	print_light(rt->light);
	print_fig(rt->fig);
}

void	print_amblight(t_amblight *amb)
{
	printf("-----------------amblight------------------\n\n");
	printf("rgb: %f, %f, %f\n", amb->rgb->x, amb->rgb->y, \
		amb->rgb->z);
	printf("light_ratio: %f\n", amb->light_ratio);
	printf("-------------------------------------------\n\n");
}

void	print_camera(t_cam *cam)
{
	printf("-------------------cam--------------------\n\n");
	printf("x, y, z: %f, %f, %f\n", cam->coords->x, cam->coords->y, \
				cam->coords->z);
	printf("orient_vec: %f, %f, %f\n", cam->orient_vec->x, \
				cam->orient_vec->y, cam->orient_vec->z);
	printf("fov: %f\n", cam->fov);
	// printf("move_x, move_y: %d, %d\n", cam->move_x, cam->move_y);
	printf("------------------------------------------\n\n");
}

void	print_light(t_light *light)
{
	t_light	*_light;

	_light = light;
	printf("------------------light-------------------\n\n");
	while (_light)
	{
		printf("x, y, z: %f, %f, %f\n", _light->xyz->x, _light->xyz->y, \
				_light->xyz->z);
		printf("rgb: %f, %f, %f\n", _light->rgb->x, \
				_light->rgb->y, _light->rgb->z);
		printf("brightness: %f\n", _light->brightness);
		printf("------------------------------------------\n\n");
		_light = _light->next;
	}
}

void	print_fig(t_fig *fig)
{
	t_fig	*_fig;

	_fig = fig;
	printf("------------------figure-------------------\n\n");
	while (_fig)
	{
		printf("type: %d\n", _fig->type);
		printf("diameter: %f\n", _fig->diameter);
		printf("height: %f\n", _fig->height);
		printf("x, y, z: %f, %f, %f\n", _fig->xyz->x, _fig->xyz->y, \
				_fig->xyz->z);
		printf("norm_vec: %f, %f, %f\n", _fig->normal_vec->x, \
				_fig->normal_vec->y, _fig->normal_vec->z);
		printf("rgb: %f, %f, %f\n", _fig->rgb->x, _fig->rgb->y, \
				_fig->rgb->z);
		printf("-------------------------------------------\n\n");
		_fig = _fig->next;
	}
}
