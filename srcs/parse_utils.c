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

#include "minirt.h"

int	ft_iscomma(int c)
{
	return (c == ',');
}

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
	char	**tmp;

	tmp = ft_split(arg, ft_iscomma);
	if (!tmp)
	{
		vec->error = MEM_ALLOC_ERR;
		return (0);
	}
	if (get_arg_len(tmp) != 3)
	{
		vec->error = FORMAT_ERR;
		return (free_args(tmp), 0);
	}
	vec->x = ft_atod(tmp[0]);
	vec->y = ft_atod(tmp[1]);
	vec->z = ft_atod(tmp[2]);
	if (!is_double_range(vec->x, range_min, range_max)
	|| !is_double_range(vec->y, range_min, range_max)
	|| !is_double_range(vec->z, range_min, range_max))
	{
		vec->error = RANGE_ERR;
		return (free_args(tmp), 0);
	}
	return (free_args(tmp), 1);
}

void	*lst_addback(t_rt *rt, t_type type)
{
	void	*tmp;
	void	*alloc;

	if (type == FIG)
	{
		alloc = init_fig();
		if (!alloc)
			return (NULL);
		if (!rt->fig)
			rt->fig = alloc;
		else
		{
			tmp = rt->fig;
			while (((t_fig *)tmp)->next)
				tmp = ((t_fig *)tmp)->next;
			((t_fig *)tmp)->next = (t_fig *)alloc;
		}
	}
	if (type == LIGHT)
	{
		alloc = init_light();
		if (!alloc)
			return (NULL);
		if (!rt->light)
			rt->light = alloc;
		else
		{
			tmp = rt->light;
			while (((t_light *)tmp)->next)
				tmp = ((t_light *)tmp)->next;
			((t_light *)tmp)->next = (t_light *)alloc;
		}
	}
	return (alloc);
}
