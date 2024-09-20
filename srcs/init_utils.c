/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
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
	light->ch = 0;
	light->next = NULL;
	light->is_click = -1;
	light->xyz = (t_vector){0, 0, 0, NULL};
	light->rgb = (t_vector){0, 0, 0, NULL};
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
	fig->xyz = (t_vector){0, 0, 0, NULL};
	fig->normal_vec = (t_vector){0, 0, 0, NULL};
	fig->rgb = (t_vector){0, 0, 0, NULL};
	fig->rgb2 = (t_vector){0, 0, 0, NULL};
	fig->right_vec = (t_vector){0, 0, 0, NULL};
	fig->up_vec = (t_vector){0, 0, 0, NULL};
	return (fig);
}

void	init_map(t_rt *rt)
{
	int	i;

	i = -1;
	rt->map = (char **)ft_calloc((WINDOW_HEIGHT + 1), sizeof(char *));
	if (!rt->map)
		close_all(rt, MEM_ALLOC_ERR);
	while (++i < WINDOW_HEIGHT)
	{
		rt->map[i] = (char *)ft_calloc((WINDOW_WIDTH + 1), sizeof(char));
		if (!rt->map[i])
			close_all(rt, MEM_ALLOC_ERR);
	}	
}
