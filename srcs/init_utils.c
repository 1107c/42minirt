/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_xss.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:21:15 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/18 11:43:24 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_light	*init_light(void)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->brightness = 0;
	light->next = NULL;
	light->is_click = -1;
	light->xyz = init_vector(0, 0, 0);
	light->rgb = init_vector(0, 0, 0);
	return (light);
}

t_fig	*init_fig(void)
{
	t_fig	*fig;

	fig = malloc(sizeof(t_fig));
	if (!fig)
		return (NULL);
	fig->type = PLANE;
	fig->diameter = 0;
	fig->height = 0;
	fig->next = NULL;
	fig->is_click = -1;
	fig->is_check = -1;
	fig->is_bump = -1;
	fig->xyz = init_vector(0, 0, 0);
	fig->normal_vec = init_vector(0, 0, 0);
	fig->rgb = init_vector(0, 0, 0);
	fig->rgb2 = init_vector(0, 0, 0);
	fig->right_vec = init_vector(0, 0, 0);
	fig->up_vec = init_vector(0, 0, 0);
	return (fig);
}

void	init_map(t_rt *rt)
{
	int	i;

	i = -1;
	rt->fast = -1;
	rt->map = (char **)ft_calloc((WINDOW_HEIGHT + 1), sizeof(char *));
	if (!rt->map)
		close_all(rt, MEM_ALLOC_ERR);
	while (++i < WINDOW_HEIGHT)
	{
		rt->map[i] = (char *)ft_calloc((WINDOW_WIDTH + 1), sizeof(char));
		if (!rt->map[i])
		{
			free_args(rt->map);
			close_all(rt, MEM_ALLOC_ERR);
		}
	}
}

t_bump	*init_bump(void)
{
	t_bump	*bump;

	bump = malloc(sizeof(t_bump));
	if (!bump)
		return (NULL);
	bump->normal_map = NULL;
	bump->color_map = NULL;
	bump->normal_height = 0;
	bump->normal_width = 0;
	bump->next = NULL;
	return (bump);
}

t_vector	init_vector(double x, double y, double z)
{
	return ((t_vector){x, y, z, NULL});
}
