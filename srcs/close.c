/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:07:25 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/16 06:36:18 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	close_mlx(t_rt *rt)
{
	mlx_destroy_image(rt->mlx, rt->img->img);
	mlx_destroy_window(rt->mlx, rt->win);
	mlx_destroy_display(rt->mlx);
	free(rt->mlx);
	free(rt->img);
}

void	close_all(t_rt *rt, char *error_msg)
{
	close_mlx(rt);
	free_args(rt->map);
	free(rt->amblight);
	free(rt->cam);
	free(rt->line);
	if (rt->file_fd)
		close(rt->file_fd);
	free_lst(rt);
	free_bump(rt->bump);
	free(rt);
	error(error_msg);
}

void	free_2d_and_close_all(t_rt *rt, char **args, char *msg)
{
	free_args(args);
	close_all(rt, msg);
}

int	close_win(t_rt *rt)
{
	close_all(rt, NULL);
	return (EXIT_SUCCESS);
}
