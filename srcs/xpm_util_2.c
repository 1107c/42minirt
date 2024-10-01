/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_util_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:53:00 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/28 17:53:00 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	interpret_xpm(int fd, t_xpm *img)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < img->info[0])
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		j = 1;
		while (tmp[j])
		{
			if (!find_color(tmp, img, i, &j))
				j++;
			if (tmp[j - 1] == '\0')
				break ;
		}
		free (tmp);
		i++;
	}
}

t_vector	**get_height_map(t_xpm *image, double **height_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < image->info[0])
	{
		j = 0;
		while (j < image->info[1])
		{
			height_map[i][j] = (0.299 * image->pixels[i][j].x) + (0.587 * \
				image->pixels[i][j].y) + (0.114 * image->pixels[i][j].z);
			j++;
		}
		i++;
	}
	return (image->pixels);
}

void	set_lrbt(int i, int j, double **height_map, double *lrbt)
{
	if (j > 0)
		lrbt[0] = height_map[i][j - 1];
	else
		lrbt[0] = height_map[i][j];
	if (i > 0)
		lrbt[3] = height_map[i - 1][j];
	else
		lrbt[3] = height_map[i][j];
}

t_vector	**translate_height_to_normal(double **height_map, t_vector \
	**normal_map, int width, int height)
{
	int		i;
	int		j;
	double	lrbt[4];

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			set_lrbt(i, j, height_map, lrbt);
			if (j < width - 1)
				lrbt[1] = height_map[i][j + 1];
			else
				lrbt[1] = height_map[i][j];
			if (i < height - 1)
				lrbt[2] = height_map[i + 1][j];
			else
				lrbt[2] = height_map[i][j];
			normal_map[i][j] = normalize_vec(cross_product((t_vector){2.0, \
				0.0, lrbt[1] - lrbt[0], 0}, (t_vector){0.0, 2.0, lrbt[2] - \
				lrbt[3], 0}));
		}
	}
	return (normal_map);
}

t_vector	**get_normal_map(t_bump *bump, t_rt *rt, char *path, int i)
{
	t_xpm	*image;
	double	**height_map;

	image = parse_xpm(path, rt, 0);
	height_map = malloc(sizeof(double *) * image->info[0]);
	bump->normal_map = malloc(sizeof(t_vector *) * image->info[0]);
	if (!height_map || !bump->normal_map)
		close_all(rt, MEM_ALLOC_ERR);
	while (++i < image->info[0])
	{
		height_map[i] = malloc(sizeof(double) * image->info[1]);
		bump->normal_map[i] = malloc(sizeof(t_vector) * image->info[1]);
		if (!height_map[i] || !bump->normal_map[i])
			close_all(rt, MEM_ALLOC_ERR);
	}
	bump->color_map = get_height_map(image, height_map);
	bump->normal_height = image->info[0];
	bump->normal_width = image->info[1];
	if (bump->normal_height < bump->normal_width)
		bump->save_height = image->info[0];
	else
		bump->save_height = image->info[1];
	free_xpm(image, height_map);
	return (translate_height_to_normal(height_map, \
			bump->normal_map, image->info[1], image->info[0]));
}
