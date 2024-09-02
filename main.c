/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:16:48 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/01 14:34:15 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	close_win(t_rt *rt);

int	main(int argc, char **argv)
{
	t_rt	*rt;
	char	*filename;

	if (argc != 2)
		error(1);
	filename = argv[1];
	rt = init_rt(filename);
	// interpret_data(rt, filename);
	draw(rt);
	mlx_hook(rt->win, 17, 1L << 0, &close_win, rt);
	mlx_key_hook(rt->win, &key_handle, rt);
	mlx_loop(rt->mlx);
	return (0);
}

int	close_win(t_rt *rt)
{
	close_all(rt, 0);
	return (0);
}
