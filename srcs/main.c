/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:16:48 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/15 18:00:47 by myeochoi         ###   ########.fr       */
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
			rt->selected_light = NULL;
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
	t_fig	*tmp, *tmp2;
	int		i;

	tmp = rt->fig;
	tmp2 = tmp;
	i = 1;
	while (tmp)
	{
		t_vector	y_unit_vector;
		t_vector	z_inv;

		y_unit_vector = (t_vector) {0, 1, 0, 0};
		z_inv = invert_vec(tmp->normal_vec);
		tmp->right_vec = invert_vec(cross_product(y_unit_vector, z_inv));
		tmp->up_vec = invert_vec(cross_product(z_inv, tmp->right_vec));
		tmp->rgb2 = tmp->rgb;
		tmp->idx = i++;
		tmp = tmp->next;
	}
	i = -1;
	rt->map = (char **)ft_calloc((WINDOW_HEIGHT + 1), sizeof(char *));
	while (++i < WINDOW_HEIGHT)
		rt->map[i] = (char *)ft_calloc((WINDOW_WIDTH + 1), sizeof(char));
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
	// print_rt(rt);
	// get_cam_basis(rt->cam);
	get_fig_idx(rt);
	draw(rt);
		// for (int i = 0; rt->map[i];++i)
		// {
		// 	for (int j = 0; rt->map[i][j]; ++j)
		// 		printf("%c ",rt->map[i][j]);
		// 	printf("\n");
		// }
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