/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:09:22 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/28 17:10:14 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	copy_matrix3(t_mat3 a, t_mat3 b);

void	mul_matrix3(t_mat3 a, t_mat3 b)
{
	t_mat3	c;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			k = -1;
			c[i][j] = 0;
			while (++k < 3)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
	copy_matrix3(a, c);
}

void	rotate_matrix(t_mat3 a, double c, double s, t_vector vec)
{
	a[0][0] = c + pow(vec.x, 2) * (1 - c);
	a[0][1] = vec.x * vec.y * (1 - c) - vec.z * s;
	a[0][2] = vec.x * vec.z * (1 - c) + vec.y * s;
	a[1][0] = vec.y * vec.x * (1 - c) + vec.z * s;
	a[1][1] = c + pow(vec.y, 2) * (1 - c);
	a[1][2] = vec.y * vec.z * (1 - c) - vec.x * s;
	a[2][0] = vec.z * vec.x * (1 - c) - vec.y * s;
	a[2][1] = vec.z * vec.y * (1 - c) + vec.x * s;
	a[2][2] = c + pow(vec.z, 2) * (1 - c);
}

void	copy_matrix3(t_mat3 a, t_mat3 b)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			a[i][j] = b[i][j];
	}
}

void	print_mat(t_mat3 a)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			printf("%lf ", a[i][j]);
		printf("\n");
	}
	printf("\n");
}
