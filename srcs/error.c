/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:04:21 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 17:42:37 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	error(char *error_msg)
{
	if (!error_msg)
		exit(EXIT_SUCCESS);
	// "usage: ./miniRT [*.rt]"
	ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	print_err(t_msg	msg, t_rt *rt)
{
	ft_putendl_fd("Error\n", 2);
	if (msg == NO_ARG)
		close_all(rt, "Error\n=> no input, enter only *.rt.");
	else if (msg == MUCH_ARG)
		close_all(rt, "Error\n=> too many input, enter only *.rt.");
	else if (msg == EXTEN_ERR)
		close_all(rt, "Error\n=> input is not .rt, enter only *.rt.");
	else if (msg == FATAL_ERR)
		close_all(rt, "Error\n=> fatal error.");
	else if (msg == OPEN_ERR)
		close_all(rt, "Error\n=> file open failed.");
}

int	open_err(int *arg, char **args, t_rt *rt)
{
	int	i;

	args += 1;
	*arg -= 1;
	i = ft_strlen(args[0]);
	if (i < 3)
		return (print_err(EXTEN_ERR, rt), 1);
	if (!((args[0][i - 3] == '.') && (args[0][i - 2] == 'r') && \
	(args[0][i - 1] == 't')))
		return (print_err(EXTEN_ERR, rt), 1);
	rt->file_name = args[0];
	rt->file_fd = open(rt->file_name, O_RDONLY);
	if (rt->file_fd < 0)
		return (print_err(OPEN_ERR, rt), 1);
	return (0);
}
