/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_util_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:53:00 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/28 17:53:00 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	skip_xpm(int fd)
{
	char	*tmp;

	while (1)
	{
		tmp = get_next_line(fd);
		if (tmp && !ft_strcmp(tmp, \
		"/* columns rows colors chars-per-pixel */\n"))
		{
			free(tmp);
			break ;
		}
		if (!tmp)
			break ;
		free(tmp);
	}
}

void	get_info_xpm(int fd, t_xpm *img)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = -1;
	k = 0;
	j = 0;
	tmp = get_next_line(fd);
	while (tmp[++i])
	{
		while (tmp[i] == '\"')
		{
			k++;
			i++;
		}
		if (tmp[i] == ' ')
		{
			tmp[i] = 0;
			img->info[j++] = ft_atoi(tmp + k);
			k = i + 1;
		}
	}
	free (tmp);
}

int	ft_sixteen(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else
		return (c - 'A' + 10);
}

void	get_rgb_xpm(int fd, t_xpm *img)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < img->info[2])
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		img->colors[i].name[0] = *(tmp + 1);
		img->colors[i].name[1] = *(tmp + 2);
		img->colors[i].rgb.x = ft_sixteen(*(tmp + 7)) \
			* 16 + ft_sixteen(*(tmp + 8));
		img->colors[i].rgb.y = ft_sixteen(*(tmp + 9)) \
			* 16 + ft_sixteen(*(tmp + 10));
		img->colors[i].rgb.z = ft_sixteen(*(tmp + 11)) \
			* 16 + ft_sixteen(*(tmp + 12));
		i++;
		free(tmp);
	}
	tmp = get_next_line(fd);
	free(tmp);
}

int	find_color(char *tmp, t_xpm *img, int i, int *j)
{
	int	idx;
	int	k;

	idx = 0;
	k = (*j - 1) / 2;
	while (idx < img->info[2])
	{
		if (ft_strncmp(tmp + *j, img->colors[idx].name, 2) == 0)
		{
			if (i < img->info[0] && k < img->info[1] && idx < img->info[2])
			{
				img->pixels[i][k].x = img->colors[idx].rgb.x;
				img->pixels[i][k].y = img->colors[idx].rgb.y;
				img->pixels[i][k].z = img->colors[idx].rgb.z;
			}
			*j += 2;
			return (1);
		}
		idx++;
	}
	return (0);
}
