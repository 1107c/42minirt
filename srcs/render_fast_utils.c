/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fast_utils.c                       	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 23:47:18 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	rt_map(int i, int j, t_worker *worker)
{
	int	x;
	int	y;

	x = 0;
	while (x < 3)
	{
		y = 0;
		while (y < 3)
		{
			worker->rt->map[j + y][i + x] = worker->rt->map[j][i];
			y++;
		}
		x++;
	}
}

void	rt_pixcel(int i, int j, t_worker *worker)
{
	int	x;
	int	y;

	x = 0;
	while (x < 3)
	{
		y = 0;
		while (y < 3)
		{
			worker->rt->pixcel_map[j + y][i + x] = \
			worker->util.color.final_color;
			worker->rt->ch_map[j + y][i + x] = 1;
			y++;
		}
		x++;
	}
}
