/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 23:47:18 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	pixel_to_image(t_image *img, double x, double y, t_vector rgb)
{
	int	pixel;
	int	color;

	color = encode_rgb(rgb.x, rgb.y, rgb.z);
	pixel = ((int)y * img->size_line) + ((int)x * 4);
	img->buffer[pixel + 0] = (color) & 0xff;
	img->buffer[pixel + 1] = (color >> 8) & 0xff;
	img->buffer[pixel + 2] = (color >> 16) & 0xff;
	img->buffer[pixel + 3] = (color >> 24);
}

int	encode_rgb(double red, double green, double blue)
{
	return ((int)red << 16 | (int)green << 8 | (int)blue);
}

void	clear_image(t_image *img)
{
	t_vector	vec;
	int			x;
	int			y;

	vec = (t_vector){0, 0, 0, 0};
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixel_to_image(img, x, y, vec);
			x++;
		}
		y++;
	}
}
