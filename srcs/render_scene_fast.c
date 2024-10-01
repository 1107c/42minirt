/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_fast.c                       	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 23:47:18 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	get_in_color(int *i, int j, t_worker *worker, t_vector point)
{
	worker->rt->map[j][*i] = draw_line(worker, point);
	worker->rt->map[j][*i + 1] = worker->rt->map[j][*i];
	worker->rt->map[j + 1][*i] = worker->rt->map[j][*i];
	worker->rt->map[j + 1][*i + 1] = worker->rt->map[j][*i];
	worker->rt->ch_map[j][*i] = 1;
	worker->rt->pixcel_map[j][*i] = worker->util.color.final_color;
	if (worker->util.before == worker->rt->map[j][*i])
	{
		worker->rt->pixcel_map[j][*i + 1] = worker->util.color.final_color;
		worker->rt->ch_map[j][*i + 1] = 1;
		worker->rt->pixcel_map[j + 1][*i + 1] = worker->util.color.final_color;
		worker->rt->ch_map[j + 1][*i + 1] = 1;
		worker->rt->pixcel_map[j + 1][*i] = worker->util.color.final_color;
		worker->rt->ch_map[j + 1][*i] = 1;
	}
	worker->util.before = worker->rt->map[j][*i];
	(*i)++;
	return (add_vec(point, mul_vec(worker->rt->cam->right_vec, 2)));
}

void	adjust_boundary(int	*i1, int *i2, int ch[WINDOW_HEIGHT]\
[WINDOW_WIDTH], int j)
{
	while (ch[j][*i1] != 1 && *i1 + 1 < WINDOW_WIDTH)
		(*i1)++;
	while (ch[j][*i2] != 1 && *i2 > 0)
		(*i2)--;
}

void	get_boundary_color(int i, int j, t_vector p[WINDOW_HEIGHT]\
[WINDOW_WIDTH], int ch[WINDOW_HEIGHT][WINDOW_WIDTH])
{
	int	i1;
	int	i2;
	int	j1;
	int	j2;

	while (++i < WINDOW_WIDTH)
	{
		if (ch[j][i] != 1)
		{
			i1 = i;
			i2 = i;
			j1 = j;
			j2 = j;
			adjust_boundary(&i1, &i2, ch, j);
			while (ch[j1][i] != 1 && j1 + 1 < WINDOW_HEIGHT)
				j1++;
			while (ch[j2][i] != 1 && j2 > 0)
				j2--;
			p[j][i].x = p[j][i1].x + p[j][i2].x + p[j1][i].x + p[j2][i].x;
			p[j][i].y = p[j][i1].y + p[j][i2].y + p[j1][i].y + p[j2][i].y;
			p[j][i].z = p[j][i1].z + p[j][i2].z + p[j1][i].z + p[j2][i].z;
			p[j][i] = mul_vec(p[j][i], 0.25);
			ch[j][i] = 1;
		}
	}
}

void	draw_point_and_init(int i, int j, t_worker *worker)
{
	j = worker->y_start - 1;
	while (++j < worker->y_end)
	{
		i = 0;
		while (i < WINDOW_WIDTH)
		{
			pixel_to_image(worker->rt->img, i, j, \
			worker->rt->pixcel_map[j][i]);
			i++;
		}
	}
	j = worker->y_start - 1;
	while (++j < worker->y_end)
	{
		i = 0;
		while (i < WINDOW_WIDTH)
		{
			worker->rt->ch_map[j][i] = 0;
			worker->rt->pixcel_map[j][i] = init_vector(0, 0, 0);
			i++;
		}
	}
}

void	*render_scene_fast(void *wk)
{
	t_worker	*worker;
	t_vector	point;
	t_vector	save;
	int			i;
	int			j;

	worker = wk;
	j = worker->y_start - 1;
	point = add_vec(worker->rt->cam->screen_origin, \
			mul_vec(worker->rt->cam->up_vec, -j));
	worker->util.before = 0;
	while (++j < worker->y_end)
	{
		i = 0;
		save = point;
		while (++i < WINDOW_WIDTH)
			point = get_in_color(&i, j, worker, point);
		j++;
		point = sub_vec(save, mul_vec(worker->rt->cam->up_vec, 2));
	}
	j = worker->y_start - 1;
	while (++j < worker->y_end)
		get_boundary_color(-1, j, worker->rt->pixcel_map, worker->rt->ch_map);
	draw_point_and_init(0, 0, worker);
	return (NULL);
}
