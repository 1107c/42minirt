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

void	print_rt(t_rt *rt)
{
	t_fig	*fig;

	fig = rt->fig;
	printf("-----------------figure------------------\n\n");
	while (fig)
	{
		printf("type: %d\n", fig->type);
		printf("diameter: %f\n", fig->diameter);
		printf("height: %f\n", fig->height);
		printf("x, y, z: %f, %f, %f\n", fig->xyz->x, fig->xyz->y, \
				fig->xyz->z);
		printf("norm_vec: %f, %f, %f\n", fig->normal_vec->x, \
				fig->normal_vec->y, fig->normal_vec->z);
		printf("rgb: %f, %f, %f\n", fig->rgb->x, fig->rgb->y, \
				fig->rgb->z);
		printf("-----------------------------------------\n\n");
		fig = fig->next;
	}
}
