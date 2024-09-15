/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:15:46 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/08 12:15:46 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	double_parse(char *arg, double *n, double range_min, double range_max)
{
	if (!is_double(arg))
		return (1);
	*n = ft_stod(arg);
	if (!is_double_range(*n, range_min, range_max))
		return (1);
	return (0);
}

int	is_double(char *arg)
{
	int	i;
	int	has_dot;
	int	has_digit;

	has_dot = 0;
	i = 0;
	has_digit = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]))
			has_digit = 1;
		else if (arg[i] == '.' && !has_dot)
			has_dot = 1;
		else
			return (0);
		i++;
	}
	return (has_digit);
}

t_light	*light_memset(t_rt *rt)
{
	t_light	*tl;

	tl = ft_calloc(sizeof(t_light), 1);
	if (!tl)
		return (0);
	light_line_up(tl, &rt->light);
	return (tl);
}

void	light_line_up(t_light *tl, t_light **light)
{
	t_light	*tmp;

	if (!(*light))
		*light = tl;
	else
	{
		tmp = *light;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = tl;
	}
}

t_object	*obj_memset(t_rt *rt, int type)
{
	t_object	*to;

	to = ft_calloc(sizeof(t_object), 1);
	if (!to)
		return (0);
	to->type = type;
	to->is_bump = 0;
	to->is_checkboard = 0;
	obj_line_up(to, &rt->obj);
	return (to);
}
