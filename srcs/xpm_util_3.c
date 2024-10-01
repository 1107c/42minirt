/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_util_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:02:34 by ksuh              #+#    #+#             */
/*   Updated: 2024/10/01 16:02:34 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	free_xpm(t_xpm *image, double **height_map)
{
	int	i;

	i = 0;
	while (i < image->info[0])
		free(height_map[i++]);
	free(image);
}