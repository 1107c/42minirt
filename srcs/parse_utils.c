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
int	is_valid_single_double_value(t_rt *rt, char *arg, double range_min, double range_max)
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
int	is_valid_multi_double_value(t_vector *vec, char *arg, double range_min, double range_max)
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
