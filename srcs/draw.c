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

static void	draw_line(t_rt *rt, t_vector point, int i, int j);
static void	checkerboard(t_rt *rt, t_vector point, t_fig *fig, double t);
static int	is_checker(double u, double v, int checker_size);

int	get_color(t_worker *worker, int x, int y)
{
	t_image	*img;
	int		pixel;
	int		color;

	color = 0;
	img = worker->rt->img;
	pixel = ((int)y * img->size_line) + ((int)x * 4);
	color += img->buffer[pixel + 3];
	color <<= 8;
	color += img->buffer[pixel + 2];
	color <<= 8;
	color += img->buffer[pixel + 1];
	color <<= 8;
	color += img->buffer[pixel];
	return (color);
}

void	set_color(t_worker *worker, int x, int y, int color)
{
	t_image	*img;
	int		pixel;

	img = worker->rt->img;
	pixel = ((int)y * img->size_line) + ((int)x * 4);
	img->buffer[pixel + 0] = (color) & 0xff;
	img->buffer[pixel + 1] = (color >> 8) & 0xff;
	img->buffer[pixel + 2] = (color >> 16) & 0xff;
	img->buffer[pixel + 3] = (color >> 24);
}

int	color_difference(int c1, int c2)
{
	int				r_diff;
	int				g_diff;
	int				b_diff;
	unsigned char	*color1;
	unsigned char	*color2;

	color1 = (unsigned char *)&c1;
	color2 = (unsigned char *)&c2;
	r_diff = abs(color1[2] - color2[2]);
	g_diff = abs(color1[1] - color2[1]);
	b_diff = abs(color1[0] - color2[0]);
	return (r_diff + g_diff + b_diff);
}

static unsigned int	clamp_color(double color)
{
	color *= 255;
	if (color > 255)
		return (255);
	if (color < 0)
		return (0);
	return (color);
}

unsigned int	create_mlx_color(t_vector *color)
{
	return (clamp_color(color->x) << 16
		| clamp_color(color->y) << 8 | clamp_color(color->z));
}

int	mix_color(int c1, int c2, double ratio)
{
	int				r;
	int				g;
	int				b;
	unsigned char	*color1;
	unsigned char	*color2;

	color1 = (unsigned char *)&c1;
	color2 = (unsigned char *)&c2;
	r = color1[2] * ratio + color2[2] * (1 - ratio);
	g = color1[1] * ratio + color2[1] * (1 - ratio);
	b = color1[0] * ratio + color2[0] * (1 - ratio);
	return (r << 16 | g << 8 | b);
}

t_color	render_pixel(t_rt *rt, t_vector point)
{
	t_fig	*fig;
	t_vec	vec;
	t_color	color;
	double	d;
	double	t;

	fig = rt->fig;
	d = INF;
	vec.fig = NULL;
	color.final_color = (t_vector) {0, 0, 0, 0};
	vec.inter_vec = (t_vector) {0, 0, 0, 0};
	vec.n_vec = (t_vector) {0, 0, 0, 0};
	while (fig)
	{
		t = get_ray_dist(point, fig, rt, &vec);
		if (t > 0 && t <= d)
		{
			d = t;
			vec.inter_tg_vec = vec.inter_vec;
			vec.n_tg_vec = vec.n_vec;
			vec.fig = fig;
		}
		fig = fig->next;
	}
	vec.inter_vec = vec.inter_tg_vec;
	vec.n_vec = vec.n_tg_vec;
	multi_lightning(rt, &vec, &color, vec.fig);
	// if (rt->selected && rt->selected->idx == vec.fig->idx && \
	// 	rt->selected->is_check == 1)
	// 	checkerboard(rt, point, vec.fig, t);
	// pixel_to_image(rt->img, i, j, color.final_color);
	return (color);
}

void	add_colors(t_vector *c1, t_vector *c2)
{
	c1->x += c2->x;
	c1->y += c2->y;
	c1->z += c2->z;
}

void	multi_colors(t_vector *c1, double d)
{
	c1->x *= d;
	c1->y *= d;
	c1->z *= d;
}

t_vector	super_sample_pixel(double x, double y, t_worker *worker)
{
	int				i;
	int				j;
	t_color			color;
	t_vector		avg_color;
	t_vector		point;

	ft_bzero(&avg_color, sizeof(t_vector));
	point = add_vec(worker->rt->cam->screen_origin, \
			mul_vec(worker->rt->cam->right_vec, x));
	point = add_vec(point, mul_vec(worker->rt->cam->up_vec, -y));
	color = render_pixel(worker->rt, point);
	add_colors(&avg_color, &color.final_color);
	// i = -1;
	// point = add_vec(point, mul_vec(worker->rt->cam->up_vec, -0.25));
	// point = add_vec(point, mul_vec(worker->rt->cam->right_vec, 0.25));
	// while (++i < 2)
	// {
	// 	j = -1;
	// 	while (++j < 2)
	// 	{
	// 		color = render_pixel(worker->rt, point);
	// 		add_colors(&avg_color, &color.final_color);
	// 		point = add_vec(point, mul_vec(worker->rt->cam->up_vec, -0.25));
	// 	}
	// 	point = add_vec(point, mul_vec(worker->rt->cam->right_vec, 0.25));
	// 	point = add_vec(point, mul_vec(worker->rt->cam->up_vec, 0.5));
	// }
	// multi_colors(&avg_color, 1.0 / (5));
	set_color(worker, x, y, create_mlx_color(&avg_color));
	return (avg_color);
}

void	fill_in_skipped_pixels_h(double x, double y, t_worker *worker,
		int threshold)
{
	int				c1;
	int				c4;

	c1 = get_color(worker, x - 1, y);
	c4 = get_color(worker, x + 2, y);
	if (color_difference(c1, c4) > threshold)
	{
		super_sample_pixel(x - 1, y, worker);
		super_sample_pixel(x, y, worker);
		super_sample_pixel(x + 1, y, worker);
		super_sample_pixel(x + 2, y, worker);
	}
	else
	{
		set_color(worker, x, y, mix_color(c1, c4, 2.0 / 3.0));
		set_color(worker, x + 1, y, mix_color(c1, c4, 1.0 / 3.0));
	}
}

void	fill_in_skipped_pixels_v(double x, double y, t_worker *worker,
		int threshold)
{
	int				c1;
	int				c4;

	if (y + 2 >= worker->y_end && y < worker->y_end)
		super_sample_pixel(x, y, worker);
	if (y + 2 >= worker->y_end && (y + 1) < worker->y_end)
		super_sample_pixel(x, y + 1, worker);
	if (y + 2 >= worker->y_end)
		return ;
	c1 = get_color(worker, x, y - 1);
	c4 = get_color(worker, x, y + 2);
	if (color_difference(c1, c4) > threshold)
	{
		super_sample_pixel(x, y - 1, worker);
		super_sample_pixel(x, y, worker);
		super_sample_pixel(x, y + 1, worker);
		super_sample_pixel(x, y + 2, worker);
	}
	else
	{
		set_color(worker, x, y, mix_color(c1, c4, 2.0 / 3.0));
		set_color(worker, x, y + 1, mix_color(c1, c4, 1.0 / 3.0));
	}
}

void	fill_in_horizontal(t_worker *worker, int threshold)
{
	int	x;
	int	y;

	y = worker->y_start - 1;
	while (++y < worker->y_end)
	{
		x = 1;
		while (x < WINDOW_WIDTH)
		{
			if (x + 2 < WINDOW_WIDTH)
				fill_in_skipped_pixels_h(x, y, worker, threshold);
			else
			{
				if (x < WINDOW_WIDTH)
					set_color(worker, x, y, get_color(worker, x - 1, y));
				if (x + 1 < WINDOW_WIDTH)
					set_color(worker, x + 1, y, get_color(worker, x, y));
			}
			x += 3;
		}

	}
}

void	fill_in_vertical(t_worker *worker, int threshold)
{
	int	x;
	int	y;

	y = worker->y_start + 1;
	while (y < worker->y_end)
	{
		x = 1;
		while (x < WINDOW_WIDTH)
		{
			if (y + 2 < WINDOW_HEIGHT)
				fill_in_skipped_pixels_v(x, y, worker, threshold);
			else
			{
				if (y < WINDOW_HEIGHT)
					set_color(worker, x, y, get_color(worker, x, y - 1));
				if (y + 1 < WINDOW_HEIGHT)
					set_color(worker, x, y + 1, get_color(worker, x, y));
			}
			x += 3;
		}
		y += 3;
	}
}

void	draw(t_rt *rt)
{
	t_worker	workers[THREADS_NUM];

	init_workers(workers, rt);
	thread_work(workers);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
}

void	*render_scene(void *wk)
{
	t_worker	*worker;
	t_vector	point;
	t_vector	p1;
	int			i;
	int			j;
	time_t			start;
	time_t			end;

	start = clock();
	worker = wk;
	j = worker->y_start;
	point = add_vec(worker->rt->cam->screen_origin, \
			mul_vec(worker->rt->cam->up_vec, -j));
	while (j < worker->y_end)
	{
		i = 0;
		p1 = point;
		while (i < WINDOW_WIDTH)
		{
			draw_line(worker->rt, point, i, j);
			point = add_vec(point, mul_vec(worker->rt->cam->right_vec, 1));
			i += 1;
			// draw_line(worker->rt, point, i, j);
			// point = add_vec(point, mul_vec(worker->rt->cam->right_vec, 1));
			// i += 2;
		}
		j += 1;
		point = sub_vec(p1, mul_vec(worker->rt->cam->up_vec, 1));
	}
	// fill_in_horizontal(worker, 25);
	end = clock();
	// fill_in_vertical(worker, 25);
	// printf("time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
	return (NULL);
}

void	draw_line(t_rt *rt, t_vector point, int i, int j)
{
	t_fig	*fig;
	t_vec	vec;
	t_color	color;
	double	d;
	double	t;

	fig = rt->fig;
	d = INF;
	vec.fig = NULL;
	color.final_color = (t_vector) {0, 0, 0, 0};
	vec.inter_vec = (t_vector) {0, 0, 0, 0};
	vec.n_vec = (t_vector) {0, 0, 0, 0};
	while (fig)
	{
		t = get_ray_dist(point, fig, rt, &vec);
		if (t > 0 && t <= d)
		{
			d = t;
			vec.inter_tg_vec = vec.inter_vec;
			vec.n_tg_vec = vec.n_vec;
			vec.fig = fig;
		}
		fig = fig->next;
	}
	vec.inter_vec = vec.inter_tg_vec;
	vec.n_vec = vec.n_tg_vec;
	if (!vec.fig)
	{
		rt->map[j][i] = 0;
		pixel_to_image(rt->img, i, j, color.final_color);
		return;		
	}
	rt->map[j][i] = vec.fig->idx + 48;
	multi_lightning(rt, &vec, &color, vec.fig);
	// if (rt->selected && rt->selected->idx == vec.fig->idx && \
	// 	rt->selected->is_check == 1)
	// 	checkerboard(rt, point, vec.fig, t);
	pixel_to_image(rt->img, i, j, color.final_color);
}

void	checkerboard(t_rt *rt, t_vector point, t_fig *fig, double t)
{
	double	uv[2];

	if (fig->type == SPHERE)
		get_sphere_uv(uv, fig, rt);
	else if (fig->type == PLANE)
		get_plane_uv(point, fig, &uv[0], &uv[1]);
	else if (fig->type == CYLINDER)
	{
		get_cylinder_uv(point, uv, fig, rt, t);
		uv[0] = fig->diameter / 2;
	}
	if (is_checker(uv[0], uv[1], 10))
		rt->color.final_color = (t_vector){fmin(255, rt->color.spe_sum.x), \
		fmin(255, rt->color.spe_sum.y), \
		fmin(255, rt->color.spe_sum.z), 0};
	else
		rt->color.final_color = (t_vector){fmin(255, 255 + \
		rt->color.spe_sum.x), fmin(255, 255 + \
		rt->color.spe_sum.y), \
		fmin(255, 255 + rt->color.spe_sum.z), 0};
}

int	is_checker(double u, double v, int checker_size)
{
	int	u_check;
	int	v_check;

	if (u < 0)
		u = -u + 0.1;
	if (v < 0)
		v = -v + 0.1;
	u_check = (int)(u * checker_size);
	v_check = (int)(v * checker_size);
	return ((u_check + v_check) % 2);
}
