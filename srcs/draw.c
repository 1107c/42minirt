/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 23:47:18 by myeochoi         ###   ########.fr       */
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
	point = init_point(rt->cam);
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


// 콘의 옆면에서 ray가 만났을 때의 법선벡터를 반환
// t_vector	get_cone_normal(t_fig *cn, t_vector inter_vec, t_vector eye)
// {
// 	t_vector	edge;
// 	t_vector	side;
// 	t_vector	norm;
// 	double		d;

// 	edge = add_vec(cn->xyz, mul_vec(cn->normal_vec, cn->height));
// 	side = normalize_vec(sub_vec(inter_vec, edge));
// 	d = -dot_product(eye, side);
// 	norm = normalize_vec(add_vec(eye, mul_vec(side, d)));
// 	return (norm);
// }

t_vector	get_cone_normal(t_fig *cn, t_vector p1, t_vector p2, double t)
{
	t_vector	d;
	t_vector	ec;
	t_vector	q;
	double		ecn;
	double		dn;
	double		r;
	double		alpha;

	d = sub_vec(p2, p1);
	ec = sub_vec(p1, cn->xyz);
	ecn = dot_product(ec, cn->normal_vec);
	dn = dot_product(d, cn->normal_vec);
	alpha = ecn + t * dn;
	r = cn->diameter * (cn->height - alpha) / (2 * cn->height);
	q = sub_vec(add_vec(ec, mul_vec(d, t)), mul_vec(cn->normal_vec, ecn + t * dn));
	q = add_vec(mul_vec(cn->normal_vec, r), mul_vec(q, cn->height - alpha));
	q = normalize_vec(q);
	return (q);
}


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
	// t_vector	local_point;



	t_vector vec1 = normalize_vec((t_vector){fig->normal_vec.y, -fig->normal_vec.x, 0, 0});
	t_vector vec2 = cross_product(fig->normal_vec, vec1);
	*u = fmod(dot_product(point, vec1) * 0.01, 1);
	*v = fmod(dot_product(point, vec2) * 0.01, 1);
}
int is_checker(double u, double v, int checker_size)
{
	if (u < 0)
		u = -u + 0.1;
	if (v < 0)
		v = -v + 0.1;
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

void	get_pl_uv(t_vector inter_vec, t_fig *fig, double *u, double *v)
{
	t_vector	tmp;
	double		u2[2];
	double		v2[2];
	double		det;

	u2[0] = fig->right_vec.x;
	u2[1] = fig->right_vec.y;
	v2[0] = fig->up_vec.x;
	v2[1] = fig->up_vec.y;
	tmp = sub_vec(inter_vec, fig->xyz);
	if (fig->right_vec.x == 0 && fig->up_vec.x == 0)
	{
		u2[0] = fig->right_vec.z;
		v2[0] = fig->up_vec.z;
		tmp.x = tmp.z;
	}
	if (fig->right_vec.y == 0 && fig->up_vec.y == 0)
	{
		u2[1] = fig->right_vec.z;
		v2[1] = fig->up_vec.z;
		tmp.y = tmp.z;
	}
	det = u2[0] * v2[1] - u2[1] * v2[0];
	*u = 0.05 * (v2[1] * tmp.x - v2[0] * tmp.y) / det;
	*v = 0.05 * (-u2[1] * tmp.x - u2[0] * tmp.y) / det;
}

void	get_cylinder_uv(t_vector p, double h, double *u, double *v)
{
	double	theta;
	double	raw_u;
	// double	u1;
	// double	v1;

	// u1 = p.x;
	// v1 = p.z;
	// if (fabs(p.x) < EPSILON)
	// 	u1 = p.y;
	// if (fabs(p.z) < EPSILON)
	// 	v1 = p.y;
	(void) h;
	// theta = atan2(u1, v1);
	theta = atan2(p.x, p.z);
	raw_u = theta / (2 * M_PI);
	// printf("theta, raw_u: %lf, %lf\n", theta, raw_u);
	*u = 1 - (raw_u + 0.5);
	// *v = h - floor(h);
	*v = p.y - floor(p.y);
	// printf("u, v: %lf %lf\n", *u, *v);
	// *u *= 0.05;
	// *v *= 0.05;
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
			else if (fig->type == CYLINDER)
			{
				n_vec = sub_vec(inter_vec, fig->xyz);
				double theta = dot_product(n_vec, fig->normal_vec) / sqrt(dot_product(n_vec, n_vec));
				n_vec = sub_vec(n_vec, mul_vec(fig->normal_vec, theta));
				n_vec = normalize_vec(n_vec);
			}
			else if (fig->type == CONE)
			{
				n_vec = get_cone_normal(fig, rt->cam->coords, point, t);
			}
		}
		if (t >= 0 && t <= d)
		{
			d = t;
			double ambient_strength = 0.85;
			double diffuse_strength = 0.35;
			double specular_strength = 0.2;
			double shininess = 128.0;

			t_light *tmp;

			tmp = rt->light;
			t_vector diffuse_sum = (t_vector){0,0,0,0};
			t_vector specular_sum = (t_vector){0,0,0,0};
			while (tmp)
			{
				l_vec = normalize_vec(sub_vec(tmp->xyz, inter_vec));
				// if (fig->type == PLANE)
				// 	r_vec = normalize_vec(sub_vec(mul_vec(n_vec, 2 * dot_product(n_vec, l_vec)), l_vec));
				// else
					r_vec = (normalize_vec(sub_vec(mul_vec(n_vec, 2 * dot_product(n_vec, l_vec)), l_vec)));
				if (!is_in_shadow(rt, inter_vec, l_vec, tmp))
				{
					diffuse_color = mul_vec((t_vector){fmin(255, fmax(0, fig->rgb.x * tmp->rgb.x)),fmin(255, fmax(0, fig->rgb.y * tmp->rgb.y)), fmin(255, fmax(0, fig->rgb.z * tmp->rgb.z)),0}, fmax(0.0, dot_product(n_vec, l_vec)) * tmp->brightness * diffuse_strength);
					specular_color = mul_vec(tmp->rgb, pow(fmax(0.0, dot_product(e_vec, r_vec)), shininess) * tmp->brightness * specular_strength);
					diffuse_sum = add_vec(diffuse_sum, diffuse_color);
					specular_sum = add_vec(specular_sum, specular_color);
				}
				specular_color = mul_vec(tmp->rgb, pow(fmax(0.0, dot_product(e_vec, r_vec)), shininess) * tmp->brightness * specular_strength);
				specular_sum = add_vec(specular_sum, specular_color);
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

				if (fig->type == SPHERE)
				{
					local_point = normalize_vec(sub_vec(inter_vec, fig->xyz));
					get_sphere_uv(local_point, &u, &v);
				}
				else if (fig->type == PLANE)
				{
					// get_pl_uv(inter_vec, fig, &u, &v);
					// printf("u, v: %lf, %lf\n", u, v);
					get_plane_uv(point, fig, &u, &v);
				}
				else if (fig->type == CYLINDER)
				{
					double	dn = dot_product(sub_vec(point, rt->cam->coords), \
								 fig->normal_vec);
					double	h = dot_product(rt->cam->coords, fig->normal_vec) \
								+ t * dn \
								- dot_product(fig->xyz, fig->normal_vec);
					local_point = add_vec(fig->xyz, mul_vec(fig->normal_vec, h));
					local_point = sub_vec(inter_vec, local_point);
					// local_point = sub_vec(inter_vec, fig->xyz);
					local_point = normalize_vec(local_point);
					get_cylinder_uv(local_point, h, &u, &v);
					u *= fig->diameter / 2;
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
