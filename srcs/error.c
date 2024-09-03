/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:04:21 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/01 11:21:34 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	error(int error_num)
{
	if (error_num == 1)
		ft_putendl_fd("usage: ./miniRT [*.rt]", STDERR_FILENO);
	exit(error_num);
}
