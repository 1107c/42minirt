/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:21:15 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 17:21:24 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_light	*init_light()
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->xyz = init_vector();
	light->rgb = init_vector();
	if (!light->xyz || !light->rgb)
		return (free(light->xyz), free(light->rgb), free(light), NULL);
	light->brightness = 0;
	light->ch = 0;
	light->next = NULL;
	return (light);
}

t_fig	*init_fig()
{
	t_fig	*fig;

	fig = malloc(sizeof(t_fig));
	if (!fig)
		return (NULL);
	fig->type = PLANE;
	fig->xyz = init_vector();
	fig->normal_vec = init_vector();
	fig->rgb = init_vector();
	if (!fig->xyz || !fig->normal_vec || !fig->rgb)
		return (free(fig->xyz), free(fig->normal_vec), free(fig->rgb), NULL);
	fig->diameter = 0;
	fig->height = 0;
	fig->next = NULL;
	return (fig);
}