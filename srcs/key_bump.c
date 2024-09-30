/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:53:00 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/28 17:53:00 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

char	*get_xpm_name_2(t_path path)
{
	if (path == PATH_10)
		return ("input_bonus/neptune.xpm");
	if (path == PATH_11)
		return ("input_bonus/saturn.xpm");
	if (path == PATH_12)
		return ("input_bonus/sun.xpm");
	if (path == PATH_13)
		return ("input_bonus/uranus.xpm");
	if (path == PATH_14)
		return ("input_bonus/venus.xpm");
	return (NULL);
}

char	*get_xpm_name(t_path path)
{
	if (path == PATH_1)
		return ("input_bonus/earthmap.xpm");
	if (path == PATH_2)
		return ("input_bonus/icecream2.xpm");
	if (path == PATH_3)
		return ("input_bonus/rock.xpm");
	if (path == PATH_4)
		return ("input_bonus/waffle.xpm");
	if (path == PATH_5)
		return ("input_bonus/block.xpm");
	if (path == PATH_6)
		return ("input_bonus/jupiter.xpm");
	if (path == PATH_7)
		return ("input_bonus/mars.xpm");
	if (path == PATH_8)
		return ("input_bonus/mercury.xpm");
	if (path == PATH_9)
		return ("input_bonus/moon.xpm");
	return (get_xpm_name_2(path));
}

t_xpm	*parse_xpm(char *path, t_rt *rt, int i)
{
	int		fd;
	t_xpm	*img;

	img = (t_xpm *)malloc(sizeof(t_xpm));
	if (!img)
		close_all(rt, MEM_ALLOC_ERR);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		close_all(rt, "Error\n=> failed to open xpm file");
	skip_xpm(fd);
	get_info_xpm(fd, img);
	get_rgb_xpm(fd, img);
	img->pixels = malloc(sizeof(t_vector *) * img->info[0]);
	if (!img->pixels)
		close_all(rt, MEM_ALLOC_ERR);
	while (i < img->info[0])
	{
		img->pixels[i++] = malloc(sizeof(t_vector) * img->info[1]);
		if (!img->pixels[i - 1])
			close_all(rt, MEM_ALLOC_ERR);
	}
	interpret_xpm(fd, img);
	close(fd);
	return (img);
}

void	key_bump_next(int keycode, t_rt *rt)
{
	if (keycode == KEY_N && rt->selected->is_bump == 1)
	{
		if (rt->bump_cnt < 14)
		{
			rt->selected->bump->next = init_bump();
			if (!rt->selected->bump->next)
				close_all(rt, MEM_ALLOC_ERR);
			rt->selected->bump = rt->selected->bump->next;
			get_normal_map(rt->selected->bump, rt, \
			get_xpm_name(rt->bump_cnt++), -1);
		}
		else if (rt->selected->bump->next == NULL)
			rt->selected->bump = rt->bump;
		else
			rt->selected->bump = rt->selected->bump->next;
		draw(rt);
	}
}

void	key_bump(int keycode, t_rt *rt, t_fig *fig)
{
	if (keycode == KEY_B)
	{
		if (rt->selected && rt->selected->is_bump == -1)
		{
			if (rt->did_get_normal_map == 0)
			{
				rt->selected->bump = init_bump();
				if (!rt->selected->bump)
					close_all(rt, MEM_ALLOC_ERR);
				rt->bump = rt->selected->bump;
				while (fig)
				{
					fig->bump = rt->selected->bump;
					fig = fig->next;
				}
				rt->selected->bump->normal_map = \
				get_normal_map(rt->selected->bump, \
				rt, get_xpm_name(rt->bump_cnt++), -1);
				rt->did_get_normal_map = 1;
			}
		}
		rt->selected->is_bump *= -1;
		draw(rt);
	}
	key_bump_next(keycode, rt);
}
