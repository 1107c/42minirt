/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:21:07 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/08 12:21:07 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	print_err(char *s)
{
	ft_putendl_fd(s, 2);
	return (1);
}

void	mlx_error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(EXIT_FAILURE);
}
