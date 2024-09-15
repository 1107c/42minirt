/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/14 22:17:19 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	pixel_to_image(t_image *img, double x, double y, t_vector rgb);
static void	draw_line(t_rt *rt, t_vector point, int i, int j);
static int	encode_rgb(double red, double green, double blue);

void	draw(t_rt *rt)
{
	t_vector	point;
	int			i;
	int			j;

	i = -1;
	j = -1;
	point = (t_vector){rt->cam->coords.x + rt->cam->distance_to_view * rt->cam->orient_vec.x - 960 * rt->cam->right_vec.x + 540 * rt->cam->up_vec.x,
		rt->cam->coords.y + rt->cam->distance_to_view * rt->cam->orient_vec.y - 960 * rt->cam->right_vec.y + 540 * rt->cam->up_vec.y,
		rt->cam->coords.z + rt->cam->distance_to_view * rt->cam->orient_vec.z - 960 * rt->cam->right_vec.z + 540 * rt->cam->up_vec.z, NULL};
	while (++j < WINDOW_HEIGHT)
	{
		while (++i < WINDOW_WIDTH)
		{
			rt->cam->ray = cam_ray(rt->cam, rt, i, j);
			draw_line(rt, point, i, j);
			point = add_vec(point, rt->cam->right_vec);
		}
		point = sub_vec(point, add_vec(mul_vec(rt->cam->right_vec, i), \
		rt->cam->up_vec));
		i = -1;
	}
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
}

// void	draw_line(t_rt *rt, t_vector point, int i, int j)
// {
// 	t_fig	*fig;
// 	double	d;
// 	double	t;

// 	fig = rt->fig;
// 	d = INF;
// 	while (fig)
// 	{
// 		if (fig->type == 0)
// 			// t = intersect_plane(fig, rt->cam->ray);
// 			t = intersect_plane(fig, rt->cam->coords, point);
// 		else if (fig->type == 1)
// 			t = intersect_sphere(fig, rt->cam->coords, point);
// 		// else if (fig->type == 2)
// 		// 	t = intersect_cylinder(fig, rt->cam->coords, point);
// 		else if (fig->type == 3)
// 			t = intersect_cone(fig, rt->cam->coords, point);
// 		if (t >= 0 && t < d)
// 		{
// 			d = t;
// 			pixel_to_image(rt->img, i, j, fig->rgb);
// 		}
// 		fig = fig->next;
// 	}
// }

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

t_vector apply_tone_mapping(t_vector color) {
    double exposure = 1.0;
    t_vector mapped_color;
    mapped_color.x = color.x * exposure / (color.x * exposure + 1.0);
    mapped_color.y = color.y * exposure / (color.y * exposure + 1.0);
    mapped_color.z = color.z * exposure / (color.z * exposure + 1.0);
    return mapped_color;
}

double apply_gamma(double value, double gamma) {
    return pow(value / 255.0, 1.0 / gamma) * 255.0;
}

void draw_line(t_rt *rt, t_vector point, int i, int j)
{
    t_fig *fig;
    double d, t;
    t_vector inter_vec, n_vec, l_vec, e_vec, r_vec, amb;
    t_vector diffuse_color, specular_color, final_color;

    fig = rt->fig;
    d = INF;
	int	flg;
	flg = 0;
    while (fig)
    {
        if (fig->type == PLANE)
		{
			t = intersect_plane(fig, rt->cam->coords, point);
			inter_vec = add_vec(rt->cam->coords, mul_vec(sub_vec(point, rt->cam->coords), t));
			l_vec = normalize_vec(sub_vec(rt->light->xyz, inter_vec));
			e_vec = normalize_vec(sub_vec(rt->cam->coords, inter_vec));
			n_vec = invert_vec(fig->normal_vec);
			r_vec = sub_vec(mul_vec(n_vec, 2 * dot_product(n_vec, l_vec)), l_vec);
		}
		else if (fig->type == SPHERE)
		{
            t = intersect_sphere(fig, rt->cam->coords, point);
			inter_vec = add_vec(rt->cam->coords, mul_vec(sub_vec(point, rt->cam->coords), t));
			l_vec = normalize_vec(sub_vec(rt->light->xyz, inter_vec));
			e_vec = normalize_vec(sub_vec(rt->cam->coords, inter_vec));
			n_vec = normalize_vec(sub_vec(inter_vec, fig->xyz));
			r_vec = sub_vec(mul_vec(n_vec, 2 * dot_product(n_vec, l_vec)), l_vec);
		}
		else if (fig->type == CYLINDER || fig->type == CONE)
		{
			if (fig->type == CYLINDER)
				t = intersect_cylinder(fig, rt->cam->coords, point, &flg);
			else
				t = intersect_cone(fig, rt->cam->coords, point, &flg);
			inter_vec = add_vec(rt->cam->coords, mul_vec(sub_vec(point, rt->cam->coords), t));
			l_vec = normalize_vec(sub_vec(rt->light->xyz, inter_vec));
			e_vec = normalize_vec(sub_vec(rt->cam->coords, inter_vec));
			if (flg == 1)
				n_vec = fig->normal_vec;
			else
			{
				n_vec = sub_vec(inter_vec, fig->xyz);
				double theta = dot_product(n_vec, fig->normal_vec) / sqrt(dot_product(n_vec, n_vec));
				n_vec = sub_vec(n_vec, mul_vec(fig->normal_vec, theta));
				n_vec = normalize_vec(n_vec);
			}
			r_vec = sub_vec(mul_vec(n_vec, 2 * dot_product(n_vec, l_vec)), l_vec);
		}
		if (t >= 0 && t <= d)
		{
			d = t;
			double ambient_strength = 0.85;
			double diffuse_strength = 0.35;
			double specular_strength = 0.9;
			double shininess = 128.0;

			amb = mul_vec(fig->rgb, rt->amblight->light_ratio * ambient_strength);
			diffuse_color = mul_vec(fig->rgb, fmax(0.0, dot_product(n_vec, l_vec)) * rt->light->brightness * diffuse_strength);
			specular_color = mul_vec(rt->light->rgb, pow(fmax(0.0, dot_product(e_vec, r_vec)), shininess) * rt->light->brightness * specular_strength);

			//printf("amb : %f %f %f\n", amb.x, amb.y, amb.z);
			final_color.x = fmin(255, amb.x + diffuse_color.x + specular_color.x);
			final_color.y = fmin(255, amb.y + diffuse_color.y + specular_color.y);
			final_color.z = fmin(255, amb.z + diffuse_color.z + specular_color.z);
			pixel_to_image(rt->img, i, j, final_color);
		}
        fig = fig->next;
    }
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
