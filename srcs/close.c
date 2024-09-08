/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:07:25 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/08 12:53:41 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	close_all(t_rt *rt, char *error_msg)
{
	mlx_destroy_image(rt->mlx, rt->img->img);
	mlx_destroy_window(rt->mlx, rt->win);
	mlx_destroy_display(rt->mlx);
	free(rt->cam->coords);
	free(rt->cam->right_vec);
	free(rt->cam->up_vec);
	free(rt->cam->corner_vec);
	free(rt->cam->orient_vec);
	free(rt->amblight->rgb);
	free(rt->light->xyz);
	free(rt->light->rgb);
	free(rt->img);
	free(rt->cam);
	t_fig *tmp;
	while (rt->fig)
	{
		//printf("fig : %d\n", rt->fig->type);
		tmp = rt->fig;
		rt->fig = rt->fig->next;
		free(tmp->xyz);
		free(tmp->normal_vec);
		free(tmp->rgb);
		free(tmp);
	}
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
