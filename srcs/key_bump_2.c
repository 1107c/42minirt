/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bump_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:08:14 by ksuh              #+#    #+#             */
/*   Updated: 2024/10/01 16:08:14 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	key_checkboard_bump(int keycode, t_rt *rt)
{
	t_fig	*fig;

	fig = rt->fig;
	if (rt->selected && rt->selected->is_check == -1 && keycode == KEY_SPACE)
		rt->selected->is_check *= -1;
	else if (rt->selected && rt->selected->is_check == 1 && keycode == \
		KEY_SPACE)
		rt->selected->is_check *= -1;
	else
		key_bump(keycode, rt, fig);
}
