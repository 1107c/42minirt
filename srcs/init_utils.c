/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:21:15 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/15 17:53:39 by myeochoi         ###   ########.fr       */
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
	return (fig);
}
