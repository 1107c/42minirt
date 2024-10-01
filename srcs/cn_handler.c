/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:17:27 by ksuh              #+#    #+#             */
/*   Updated: 2024/10/01 13:17:27 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	cone1(t_fig *cn, t_xs *xs)
{
	(void) cn;
	if (xs->t[0] > 0)
		return (xs->t[0]);
	else if (xs->t[1] > 0)
	{
		xs->flag = 3;
		return (xs->t[1]);
	}
	return (-1.0);
}

double	cone2(t_fig *cn, t_xs *xs)
{
	if (xs->t[1] < 0)
		return (-1.0);
	else if (xs->left >= xs->c && xs->right >= xs->c)
	{
		xs->flag = 3;
		return (xs->t[1]);
	}
	else if (xs->alpha < 0)
	{
		xs->flag = 2;
		return (get_cn_center_hit(cn, xs, cn->xyz));
	}
	xs->flag = 1;
	return (get_cn_center_hit(cn, xs, cn->top));
}

double	cone3(t_fig *cn, t_xs *xs)
{
	if (xs->t[0] > 0)
		return (xs->t[0]);
	else if (xs->left >= xs->c && xs->right >= xs->c)
	{
		xs->flag = 3;
		if (xs->alpha < cn->height)
			return (get_cn_center_hit(cn, xs, cn->xyz));
		return (get_cn_center_hit(cn, xs, cn->top));
	}
	return (-1.0);
}

double	cone4(t_fig *cn, t_xs *xs)
{
	if (xs->t[1] < 0)
	{
		if (xs->left >= xs->c && xs->right >= xs->c)
		{
			xs->flag = 3;
			if (xs->beta <= cn->height)
				return (get_cn_center_hit(cn, xs, cn->xyz));
			return (get_cn_center_hit(cn, xs, cn->top));
		}
		return (-1.0);
	}
	else if (xs->t[0] < 0)
		return (xs->t[1]);
	else if (xs->left >= xs->c && xs->right >= xs->c)
	{
		xs->flag = 3;
		return (xs->t[0]);
	}
	else if (xs->alpha < 0)
	{
		xs->flag = 2;
		return (get_cn_center_hit(cn, xs, cn->xyz));
	}
	xs->flag = 1;
	return (get_cn_center_hit(cn, xs, cn->top));
}

double	cone5(t_fig *cn, t_xs *xs)
{
	if (xs->alpha < 0 || xs->alpha > xs->h)
	{
		if (xs->t[1] > 0)
			return (xs->t[1]);
		if (xs->left >= xs->c && xs->right >= xs->c)
		{
			xs->flag = 3;
			if (xs->alpha < 0)
				return (get_cn_center_hit(cn, xs, cn->top));
			return (get_cn_center_hit(cn, xs, cn->xyz));
		}
		return (-1.0);
	}
	if (xs->t[0] < 0)
		return (-1.0);
	xs->flag = 3;
	if (xs->left >= xs->c && xs->right >= xs->c)
		return (xs->t[0]);
	if (xs->alpha < cn->height)
	{
		xs->flag = 2;
		return (get_cn_center_hit(cn, xs, cn->xyz));
	}
	xs->flag = 1;
	return (get_cn_center_hit(cn, xs, cn->top));
}
