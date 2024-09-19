/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 23:24:09 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//static void	pixel_to_image(t_image *img, double x, double y, t_vector rgb);
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
			// rt->cam->ray = cam_ray(rt->cam, rt, i, j);
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


void get_sphere_uv(t_vector point, double *u, double *v)
{
	*u = 0.5 + (atan2(point.z, point.x)) / (2 * M_PI);
	*v = 0.5 + asin(point.y) / M_PI;
}

void get_plane_uv(t_vector point, t_fig *fig, double *u, double *v)
{
	//t_vector	local_point;
// t_vector right_normalized = normalize_vec(fig->right_vec);
// t_vector up_normalized = normalize_vec(fig->up_vec);

	//local_point =  mul_vec(sub_vec(point, fig->normal_vec), 0.002);
	// *u = dot_product(local_point, fig->right_vec) / dot_product(fig->right_vec, fig->right_vec);
	// *v = dot_product(local_point, fig->up_vec) / dot_product(fig->up_vec, fig->up_vec);
	// fig->up_vec.y = 1;
	// fig->right_vec.z = 1;
	// fig->up_vec.z = 1;
	// t_vector	up_vec = normalize_vec(cross_product(fig->normal_vec, (t_vector){1, 0, 0, 0}));
	// if (sqrt(dot_product(up_vec, up_vec)) == 0)
	// 	up_vec = normalize_vec(cross_product(fig->normal_vec, (t_vector){0, 0, 1, 0}));
	// t_vector right_vec = normalize_vec(cross_product(up_vec, fig->normal_vec));
	t_vector vec1 = normalize_vec((t_vector){fig->normal_vec.y, -fig->normal_vec.x, 0, 0});
	t_vector vec2 = cross_product(fig->normal_vec, vec1);
	*u = fmod(dot_product(point, vec1) * 0.01, 1);
	*v = fmod(dot_product(point, vec2) * 0.01, 1);
}
int is_checker(double u, double v, int checker_size)
{
	int u_check = (int)(u * checker_size);
	int v_check = (int)(v * checker_size);
	return ((u_check + v_check) % 2);
}
int is_in_shadow(t_rt *rt, t_vector inter_vec, t_vector light_dir, t_light *light)
{
	t_fig *fig;
	double t, max_t;
	int flg;

	fig = rt->fig;
	max_t = sqrt(dot_product ((sub_vec(light->xyz, inter_vec)), sub_vec(light->xyz, inter_vec)));

	while (fig)
	{
		flg = 0;
		if (fig->type == PLANE)
			t = intersect_plane(fig, inter_vec, add_vec(inter_vec, light_dir));
		else if (fig->type == SPHERE)
			t = intersect_sphere(fig, inter_vec, add_vec(inter_vec, light_dir));
		else if (fig->type == CYLINDER)
			t = intersect_cylinder(fig, inter_vec, add_vec(inter_vec, light_dir), &flg);
		else if (fig->type == CONE)
			t = intersect_cone(fig, inter_vec, add_vec(inter_vec, light_dir));
		if (t > 0.001 && t < max_t)
			return (1);
		fig = fig->next;
	}
	return (0);
}


void draw_line(t_rt *rt, t_vector point, int i, int j)
{
	t_fig *fig;
	double d, t;
	t_vector inter_vec, n_vec, l_vec, e_vec, r_vec, amb;
	t_vector diffuse_color, specular_color, final_color;

	fig = rt->fig;
	d = INF;
	int flg;
	while (fig)
	{
		flg = 0;
		if (fig->type == PLANE)
		{
			t = intersect_plane(fig, rt->cam->coords, point);
			inter_vec = add_vec(rt->cam->coords, mul_vec(sub_vec(point, rt->cam->coords), t));
			e_vec = normalize_vec(sub_vec(rt->cam->coords, inter_vec));
			n_vec = invert_vec(fig->normal_vec);
		}
		else if (fig->type == SPHERE)
		{
			t = intersect_sphere(fig, rt->cam->coords, point);
			inter_vec = add_vec(rt->cam->coords, mul_vec(sub_vec(point, rt->cam->coords), t));
			e_vec = normalize_vec(sub_vec(rt->cam->coords, inter_vec));
			n_vec = normalize_vec(sub_vec(inter_vec, fig->xyz));
		}
		else if (fig->type == CYLINDER || fig->type == CONE)
		{
			if (fig->type == CYLINDER)
				t = intersect_cylinder(fig, rt->cam->coords, point, &flg);
			else
				t = intersect_cone(fig, rt->cam->coords, point);
			inter_vec = add_vec(rt->cam->coords, mul_vec(sub_vec(point, rt->cam->coords), t));
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
		}
		if (t >= 0 && t <= d)
		{
			d = t;
			double ambient_strength = 0.85;
			double diffuse_strength = 0.35;
			double specular_strength = 0.9;
			double shininess = 128.0;

			t_light *tmp;

			tmp = rt->light;
			t_vector diffuse_sum = (t_vector){0,0,0,0};
			t_vector specular_sum = (t_vector){0,0,0,0};
			while (tmp)
			{
				l_vec = normalize_vec(sub_vec(tmp->xyz, inter_vec));
				if (!is_in_shadow(rt, inter_vec, l_vec, tmp))
				{
					r_vec = sub_vec(mul_vec(n_vec, 2 * dot_product(n_vec, l_vec)), l_vec);
					diffuse_color = mul_vec((t_vector){fmin(255, fmax(0, fig->rgb.x * tmp->rgb.x)),fmin(255, fmax(0, fig->rgb.y * tmp->rgb.y)), fmin(255, fmax(0, fig->rgb.z * tmp->rgb.z)),0}, fmax(0.0, dot_product(n_vec, l_vec)) * tmp->brightness * diffuse_strength);
					specular_color = mul_vec(tmp->rgb, pow(fmax(0.0, dot_product(e_vec, r_vec)), shininess) * tmp->brightness * specular_strength);
					diffuse_sum = add_vec(diffuse_sum, diffuse_color);
					specular_sum = add_vec(specular_sum, specular_color);
				}
				tmp = tmp->next;
			}
			amb = mul_vec(fig->rgb, rt->amblight->light_ratio * ambient_strength);
			final_color.x = fmin(255, amb.x + diffuse_sum.x + specular_sum.x);
			final_color.y = fmin(255, amb.y + diffuse_sum.y + specular_sum.y);
			final_color.z = fmin(255, amb.z + diffuse_sum.z + specular_sum.z);
			
			if (rt->selected && rt->selected->idx == fig->idx && rt->selected->is_check == 1)
			{
				double u, v;
				t_vector local_point;

				if (fig->type == SPHERE || fig->type == CYLINDER)
				{
					local_point = normalize_vec(sub_vec(inter_vec, fig->xyz));
					get_sphere_uv(local_point, &u, &v);
				}
				else if (fig->type == PLANE)
				{
					get_plane_uv(point, fig, &u, &v);
				}
				if (is_checker(u, v, 10))
					pixel_to_image(rt->img, i, j, (t_vector){fmin(255, specular_sum.x), fmin(255, specular_sum.y), fmin(255, specular_sum.z), 0});
				else
					pixel_to_image(rt->img, i, j, (t_vector){fmin(255, 255 + specular_sum.x), fmin(255, 255 + specular_sum.y), fmin(255, 255 + specular_sum.z), 0});
			}
			else
				pixel_to_image(rt->img, i, j, final_color);
			rt->map[j][i] = fig->idx + 48;
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
