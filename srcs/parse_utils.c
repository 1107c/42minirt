/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:13:42 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 14:22:31 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// double 자료형이 주어진 범위에 있는지 검사
int	is_double_range(double d, double range_min, double range_max)
{
	return (d >= range_min && d <= range_max);
}

// 한 개의 double 자료형 유효성 검사
int	is_valid_single_double_value(t_rt *rt, char *arg, double range_min, \
double range_max)
{
	double	d;

	if (ft_strchr(arg, ','))
	{
		rt->error = FORMAT_ERR;
		return (0);
	}
	d = ft_atod(arg);
	if (!is_double_range(d, range_min, range_max))
	{
		rt->error = RANGE_ERR;
		return (0);
	}
	return (1);
}

// vector의 double 자료형(3개) 유효성 검사
int	is_valid_multi_double_value(t_vector *vec, char *arg, double range_min, \
double range_max)
{
	char	**nums;

	nums = ft_split(arg, ft_iscomma);
	if (!nums)
	{
		vec->error = MEM_ALLOC_ERR;
		return (0);
	}
	if (get_arg_len(nums) != 3)
	{
		vec->error = FORMAT_ERR;
		return (free_args(nums), 0);
	}
	vec->x = ft_atod(nums[0]);
	vec->y = ft_atod(nums[1]);
	vec->z = ft_atod(nums[2]);
	if (!is_double_range(vec->x, range_min, range_max) \
		|| !is_double_range(vec->y, range_min, range_max) \
		|| !is_double_range(vec->z, range_min, range_max))
	{
		vec->error = RANGE_ERR;
		return (free_args(nums), 0);
	}
	return (free_args(nums), 1);
}

void	get_fig_idx_vec(t_rt *rt)
{
	t_fig		*tmp;
	int			i;
	t_vector	y_unit_vector;
	t_vector	z;

	tmp = rt->fig;
	i = 1;
	while (tmp)
	{
		if (fabs(tmp->normal_vec.y) != 1)
			y_unit_vector = init_vector(0, 0, 0);
		else
			y_unit_vector = init_vector(0, 0, 1);
		z = tmp->normal_vec;
		tmp->right_vec = normalize_vec(cross_product(y_unit_vector, z));
		tmp->up_vec = normalize_vec(cross_product(z, tmp->right_vec));
		tmp->rgb2 = tmp->rgb;
		tmp->idx = i++;
		tmp->is_check = -1;
		tmp->is_bump = -1;
		tmp = tmp->next;
	}
}
