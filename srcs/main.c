/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:16:48 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/08 12:46:34 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minirt.h"

static int	close_win(t_rt *rt);

int	main(int arg, char **args)
{
	t_rt	*rt;

	if (arg <= 1)
		return (print_err(NO_ARG, NULL), 1);
	else if (arg >= 3)
		return (print_err(MUCH_ARG, NULL), 1);
	else
	{
		rt = init_rt();
		if (!rt)
			return (print_err(FATAL_ERR, rt), 1);
		if (open_err(&arg, args, rt))
			return (1);
		parse_data(rt);
		print_rt(rt);
		draw(rt);
		mlx_key_hook(rt->win, &key_handle, rt);
		mlx_hook(rt->win, 17, 1L << 0, &close_win, rt);
		mlx_loop(rt->mlx);
	}
	return (0);
}

int	close_win(t_rt *rt)
{
	close_all(rt, NULL);
	return (0);
}
