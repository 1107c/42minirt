/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:07:25 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/03 15:07:36 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	close_all(t_rt *rt, char *error_msg)
{
	mlx_destroy_image(rt->mlx, rt->img->img);
	mlx_destroy_window(rt->mlx, rt->win);
	mlx_destroy_display(rt->mlx);
	free(rt->img);
	free(rt->cam);
	free(rt->fig);
	free(rt->light);
	free(rt->amblight);
	free(rt->mlx);
	free(rt->file_name);
	free(rt->line);
	rt->mlx = NULL;
	free(rt);
	error(error_msg);
}
