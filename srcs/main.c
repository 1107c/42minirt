/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:16:48 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/01 14:04:13 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	close_win(t_rt *rt);

void	print_err(t_msg	msg, t_rt *rt)
{
	if (msg == NO_ARG)
		ft_putendl_fd("no input, enter only *.rt.\n", 1)	;
	else if (msg == MUCH_ARG)
		ft_putendl_fd("too many input, enter only *.rt.\n", 1);
	else if (msg == EXTEN_ERR)
		ft_putendl_fd("input is not .rt, enter only *.rt.\n", 1);
	else if (msg == EXTEN_ERR)
		ft_putendl_fd("fatal error.\n", 1);
	else if (msg == OPEN_ERR)
		ft_putendl_fd("file open failed.\n", 1);
	if (rt)
		close_win(rt);
	exit (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}


int	open_err(int *arg, char **args, t_rt *rt)
{
	int	i;

	args += 1;
	*arg -= 1;
	i = ft_strlen(args[0]);
	if (!((args[0][i - 3] == '.') && (args[0][i - 2] == 'r') && \
	(args[0][i - 1] == 't')))
		return (print_err(EXTEN_ERR, rt), 1);
	rt->file_name = args[0];
	rt->file_fd = open(rt->file_name, O_RDONLY);
	if (rt->file_fd < 0)
		return (print_err(OPEN_ERR, rt), 1);
	return (0);
}

int	key_press(int keycode, t_rt *rt)
{
	if (keycode == ESC)
		close_win(rt);
	return (0);
}

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
		// interpret_data(rt, filename);
		// draw(rt);
		mlx_hook(rt->win, 2, 1L << 0, &key_press, rt);
		mlx_hook(rt->win, 17, 1L << 0, &close_win, rt);
		mlx_loop(rt->mlx);
	}
	return (0);
}

int	close_win(t_rt *rt)
{
	close_all(rt, 0);
	return (0);
}
