/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:16:48 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/18 11:17:25 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	//print_rt(rt);
	mlx_key_hook(rt->win, &key_handle, rt);
	mlx_mouse_hook(rt->win, &mouse_handle, rt);
	mlx_hook(rt->win, 17, 1L << 0, &close_win, rt);
	draw(rt);
	mlx_loop(rt->mlx);
	return (EXIT_SUCCESS);
}
