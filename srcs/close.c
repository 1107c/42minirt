/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:07:25 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 15:59:54 by myeochoi         ###   ########.fr       */
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
	free(rt->line);
	rt->mlx = NULL;
	free(rt);
	error(error_msg);
}

// 2차원 배열을 free하고 프로그램 종료
void	free_2d_and_close_all(t_rt *rt, char **args, char *msg)
{
	free_args(args);
	close_all(rt, msg);
}
