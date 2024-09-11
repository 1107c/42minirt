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
	ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	print_err(t_msg	msg)
{
	printf("Error\n");
	if (msg == NO_ARG)
		printf("=> no input, enter only *.rt");
	else if (msg == MUCH_ARG)
		printf("=> too many input, enter only *.rt");
	else if (msg == EXTEN_ERR)
		printf("=> input is not .enter only *.rt");
	else if (msg == FATAL_ERR)
		printf("=> fatal error");
	else if (msg == OPEN_ERR)
		printf("=> file open error");
	exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int	open_file(char *filename)
{
	int	fd;
	int	i;

	i = ft_strlen(filename);
	if (i < 3)
		print_err(EXTEN_ERR);
	if (ft_strcmp(filename + i - 3, ".rt"))
		print_err(EXTEN_ERR);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_err(OPEN_ERR);
	return (fd);
}
