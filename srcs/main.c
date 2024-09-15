/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:16:48 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 17:48:58 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	close_win(t_rt *rt);

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
	draw(rt);
	mlx_key_hook(rt->win, &key_handle, rt);
	mlx_hook(rt->win, 17, 1L << 0, &close_win, rt);
	mlx_loop(rt->mlx);
	return (EXIT_SUCCESS);
}

int	close_win(t_rt *rt)
{
	close_all(rt, NULL);
	return (EXIT_SUCCESS);
}