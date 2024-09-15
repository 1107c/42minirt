/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:16:48 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/16 03:44:54 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	close_win(t_rt *rt);


int	mouse_handle(int keycode, int x, int y, t_rt *rt)
{
	t_fig *tmp;
	int idx;

	tmp = rt->fig;
	idx = rt->map[y][x] - 48;
	while (tmp)
	{
		if (tmp->idx == idx && tmp->is_click == -1)
		{
			tmp->rgb = (t_vector){tmp->rgb.x * 0.75, tmp->rgb.y * 0.75, tmp->rgb.z * 0.75, 0};
			tmp->is_click *= -1;
			rt->selected = tmp;
		}
		else if ((tmp->idx != idx && tmp->is_click == 1) || (tmp->idx == idx && tmp->is_click == 1))
		{
			tmp->rgb = tmp->rgb2;
			tmp->is_click *= -1;
		}
		if (rt->selected_light)
		{
			rt->selected->is_click *= -1;
			rt->selected_light = NULL;
		}
		tmp = tmp->next;
	}
	draw(rt);
	// if (tmp->is_click)
	// {
	// 	mlx_key_hook(rt->win, &key_handle, rt);
	// }
	//printf("%d %d %d %d\n",x, y, idx, keycode);
}

void	get_fig_idx(t_rt *rt)
{
	t_fig	*tmp;
	int		i;

	tmp = rt->fig;
	i = 1;
	while (tmp)
	{
		t_vector	y_unit_vector;
		t_vector	z_inv;

		if (fabs(tmp->normal_vec.y) != 1)
			y_unit_vector = (t_vector) {0, 1, 0, 0};
		else
			y_unit_vector = (t_vector) {0, 0, -1, 0};
		z_inv = invert_vec(tmp->normal_vec);
		tmp->right_vec = invert_vec(cross_product(y_unit_vector, z_inv));
		tmp->up_vec = invert_vec(cross_product(z_inv, tmp->right_vec));
		tmp->rgb2 = tmp->rgb;
		tmp->idx = i++;
		tmp = tmp->next;
	}
	i = -1;
	rt->map = (char **)ft_calloc((WINDOW_HEIGHT + 1), sizeof(char *));
	if (!rt->map)
		close_all(rt, MEM_ALLOC_ERR);
	while (++i < WINDOW_HEIGHT)
	{
		rt->map[i] = (char *)ft_calloc((WINDOW_WIDTH + 1), sizeof(char));
		if (!rt->map[i])
			close_all(rt, MEM_ALLOC_ERR);
	}
}


int	main(int arg, char **args)
{
	t_rt	*rt;
	int		fd;

	if (arg <= 1)
		return (print_err(NO_ARG));
	else if (arg >= 3)
		return (print_err(MUCH_ARG));
	fd = open_file(args[1]);
	rt = init_rt(fd);
	if (!rt)
		return (close(fd), print_err(FATAL_ERR));
	parse_data(rt);
	set_cam(rt->cam, rt->win_x, rt->win_y);
	print_rt(rt);
	// for (t_light *l = rt->light; l; l = l->next)
	// {
	// 	printf("%f\n", l->brightness);
	// 	printf("%f %f %f\n", l->xyz.x, l->xyz.y, l->xyz.z);
	// }
	get_fig_idx(rt);
	draw(rt);
	mlx_key_hook(rt->win, &key_handle, rt);
	mlx_mouse_hook(rt->win, &mouse_handle, rt);
	mlx_hook(rt->win, 17, 1L << 0, &close_win, rt);
	mlx_loop(rt->mlx);
	return (EXIT_SUCCESS);
}

int	close_win(t_rt *rt)
{
	close_all(rt, NULL);
	return (EXIT_SUCCESS);
}