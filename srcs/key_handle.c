/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:12:55 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 13:45:30 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	key_translate(int keycode, t_rt *rt);
static void	key_rotate(int keycode, t_rt *rt);

void	fig_resize_dia(int keycode, t_rt *rt)
{
	if (keycode == NUM_PLUS && rt->selected)
	{
		if (rt->selected->type == 1)
			rt->selected->diameter += 2;
		else if (rt->selected->type == 2)
			rt->selected->diameter += 2;
		else if (rt->selected->type == 3)
			rt->selected->diameter += 2;
	}
	if (keycode == NUM_MINUS && rt->selected && rt->selected->diameter > 3)
	{
		if (rt->selected->type == 1)
			rt->selected->diameter -= 2;
		else if (rt->selected->type == 2)
			rt->selected->diameter -= 2;
		else if (rt->selected->type == 3)
			rt->selected->diameter -= 2;
	}
}

void	fig_resize_height(int keycode, t_rt *rt)
{
	if (!rt->selected)
		return ;
	if (keycode == KEY_PLUS && rt->selected->type == 2)
		rt->selected->height += 2;
	if (keycode == KEY_MINUS && rt->selected->type == 2 && \
	rt->selected->height > 3)
		rt->selected->height -= 2;
	if (keycode == KEY_PLUS && rt->selected->type == 3)
		rt->selected->height += 2;
	if (keycode == KEY_MINUS && rt->selected->type == 3 && \
	rt->selected->height > 3)
		rt->selected->height -= 2;
}

void	skip_xpm(int fd, t_xpm *img)
{
	char	*tmp;

	while (1)
    {
		tmp = get_next_line(fd);
		if (tmp && !ft_strcmp(tmp, "/* columns rows colors chars-per-pixel */\n"))
		{
			free(tmp);
			break ;
		}
		if (!tmp)
			break;
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
			break;
		img->colors[i].name[0] = *(tmp + 1);
		img->colors[i].name[1] = *(tmp + 2);
		img->colors[i].rgb.x = ft_sixteen(*(tmp + 7)) * 16 + ft_sixteen(*(tmp + 8));
		img->colors[i].rgb.y = ft_sixteen(*(tmp + 9)) * 16 + ft_sixteen(*(tmp + 10));
		img->colors[i].rgb.z = ft_sixteen(*(tmp + 11)) * 16 + ft_sixteen(*(tmp + 12));
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
			// if (i == 0)
			// 	printf("%s\n", img->colors[i].name);
			img->pixels[i][k].x = img->colors[idx].rgb.x;
			img->pixels[i][k].y = img->colors[idx].rgb.y;
			img->pixels[i][k].z = img->colors[idx].rgb.z;
			// printf("r:%d, g:%d, b:%d n:%s, r:%d, g:%d, b:%d\n", img->colors[idx].r, img->colors[idx].g, img->colors[idx].b, img->colors[0].name, img->pixels[0][0].r, img->pixels[0][0].g, img->pixels[0][0].b);
			*j += 2;
			return (1);
		}
		idx++;
	}
	return (0);
}

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
     		break;
     	j = 1;
      	while (tmp[j])
       {
       		if (!find_color(tmp, img, i, &j) && j < ft_strlen(tmp))
      			j++;
       }
     	free (tmp);
      	i++;
    }
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
	skip_xpm(fd, img);
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

void	get_height_map(t_xpm *image, double **height_map, t_bump *bump)
{
	int	i;
	int	j;

	i = 0;
    while (i < image->info[0])
    {
    	int j = 0;
		while (j < image->info[1])
		{
			height_map[i][j] = (0.299 * image->pixels[i][j].x) + (0.587 * \
				image->pixels[i][j].y) + (0.114 * image->pixels[i][j].z);
			j++;
		}
		i++;
    }
    bump->color_map = image->pixels;
}

t_vector **	translate_height_to_normal(double **height_map, t_vector **normal_map, int width, int height)
{
	int		i;
	int		j;
	double	LRBT[4];

	i = -1;
	while (++i < height)
	{
		j = 0;
		while (j < width)
		{
			if (j > 0)
            	LRBT[0] = height_map[i][j-1];
			else
				LRBT[0] = height_map[i][j];
			if (j < width - 1)
				LRBT[1] = height_map[i][j + 1];
			else
				LRBT[1] = height_map[i][j];
            if (i > 0)
           		LRBT[3] = height_map[i-1][j];
            else
            	LRBT[3] = height_map[i][j];
            if (i < height - 1)
           		LRBT[2] = height_map[i + 1][j];
            else
				LRBT[2] = height_map[i][j];
            normal_map[i][j] = normalize_vec(cross_product((t_vector){2.0, \
            0.0, LRBT[1]- LRBT[0], 0}, (t_vector){0.0, 2.0, LRBT[2] - LRBT[3], 0}));
			j++;
		}
	}
	return (normal_map);
}

void	get_normal_map(t_bump *bump, t_rt *rt, char *path)
{
    t_xpm	*image;
    double	**height_map;
    int		i;

    image = parse_xpm(path, rt, 0);
    height_map = malloc(sizeof(double*) * image->info[0]);
    bump->normal_map = malloc(sizeof(t_vector *) * image->info[0]);
    if (!height_map || !bump->normal_map)
    	close_all(rt, MEM_ALLOC_ERR);
    i = 0;
    while (i < image->info[0])
    {
    	height_map[i] = malloc(sizeof(double) * image->info[1]);
     	bump->normal_map[i] = malloc(sizeof(t_vector ) * image->info[1]);
     	if (!height_map[i] || !bump->normal_map[i])
      		close_all(rt, MEM_ALLOC_ERR);
      	i++;
    }
    get_height_map(image, height_map, bump);
    bump->normal_height = image->info[0];
    bump->normal_width = image->info[1];
    bump->normal_map = translate_height_to_normal(height_map, bump->normal_map, image->info[0], image->info[1]);
}

char *get_xpm_name(t_path path)
{
	if (path == PATH_1)
		return ("input_bonus/block.xpm");
	if (path == PATH_2)
		return ("input_bonus/icecream2.xpm");
	if (path == PATH_3)
		return ("input_bonus/rock.xpm");
	if (path == PATH_4)
		return ("input_bonus/waffle.xpm");
	if (path == PATH_5)
		return ("input_bonus/earthmap.xpm");
	if (path == PATH_6)
		return ("input_bonus/jupiter.xpm");
	if (path == PATH_7)
		return ("input_bonus/mars.xpm");
	if (path == PATH_8)
		return ("input_bonus/mercury.xpm");
	if (path == PATH_9)
		return ("input_bonus/moon.xpm");
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


void	key_bump(int keycode, t_rt *rt)
{
	t_fig	*fig;

	if (keycode == KEY_B)
	{
		if (rt->selected && rt->selected->is_bump == -1)
			if (rt->did_get_normal_map == 0)
			{
				rt->selected->bump = init_bump();
				if (!rt->selected->bump)
					close_all(rt, MEM_ALLOC_ERR);
				rt->bump = rt->selected->bump;
				fig = rt->fig;
				while (fig)
				{
					fig->bump = rt->selected->bump;
					fig = fig->next;
				}
				get_normal_map(rt->selected->bump, rt, get_xpm_name(rt->bump_cnt++));
				rt->did_get_normal_map = 1;
			}
		rt->selected->is_bump *= -1;
		draw(rt);
	}
	else if (keycode == KEY_N && rt->selected->is_bump == 1)
	{
		if (rt->bump_cnt < 14)
		{
			rt->selected->bump->next = init_bump();
			if (!rt->selected->bump->next)
				close_all(rt, MEM_ALLOC_ERR);
			rt->selected->bump = rt->selected->bump->next;
			get_normal_map(rt->selected->bump, rt, get_xpm_name(rt->bump_cnt++));
		}
		else if (rt->selected->bump->next == NULL)
			rt->selected->bump = rt->bump;
		else
			rt->selected->bump = rt->selected->bump->next;
		draw(rt);
	}
}

int	key_handle(int keycode, t_rt *rt)
{
	if (keycode == KEY_ESC)
		close_all(rt, NULL);
	else if (keycode == KEY_UP || keycode == KEY_DOWN || \
			keycode == KEY_LEFT || keycode == KEY_RIGHT)
		key_rotate(keycode, rt);
	else if (keycode == KEY_W || keycode == KEY_A || \
		keycode == KEY_S || keycode == KEY_D || \
		keycode == KEY_Q || keycode == KEY_E)
		key_translate(keycode, rt);
	else if (keycode == NUM_UP || keycode == NUM_DOWN || \
			keycode == NUM_LEFT || keycode == NUM_RIGHT || \
			keycode == NUM_FRONT || keycode == NUM_BACK)
		fig_light_translate(keycode, rt->selected, rt->selected_light);
	else if (keycode == KEY_LIGHT)
		key_light(keycode, rt);
	else if (keycode == NUM_ROT_X || keycode == NUM_ROT_Y)
		fig_rotate(keycode, rt);
	else if (keycode == NUM_PLUS || keycode == NUM_MINUS)
		fig_resize_dia(keycode, rt);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		fig_resize_height(keycode, rt);
	else if (keycode == KEY_SPACE)
		return (key_checkboard(rt), 0);
	else if (keycode == KEY_B || keycode == KEY_N)
		return (key_bump(keycode, rt), 0);
	printf("coords %f, %f, %f\n", rt->cam->coords.x, rt->cam->coords.y, rt->cam->coords.z);
	printf("orinedt %f, %f, %f\n", rt->cam->orient_vec.x, rt->cam->orient_vec.y, rt->cam->orient_vec.z);

	return (draw(rt), 0);
}

void	key_translate(int keycode, t_rt *rt)
{
	if (keycode == KEY_W)
	{
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->orient_vec, 1));
	}
	else if (keycode == KEY_S)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->orient_vec, -1));
	else if (keycode == KEY_D)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->right_vec, 1));
	else if (keycode == KEY_A)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->right_vec, -1));
	else if (keycode == KEY_Q)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->up_vec, 1));
	else if (keycode == KEY_E)
		rt->cam->coords = add_vec(rt->cam->coords, \
		mul_vec(rt->cam->up_vec, -1));
	rt->cam->screen_origin = init_point(rt->cam);
}

void	key_rotate(int keycode, t_rt *rt)
{
	if (keycode == KEY_UP)
		rt->cam->phi += 10;
	else if (keycode == KEY_DOWN)
		rt->cam->phi -= 10;
	else if (keycode == KEY_LEFT)
		rt->cam->theta -= 10;
	else if (keycode == KEY_RIGHT)
		rt->cam->theta += 10;
	if (rt->cam->theta >= 180.0)
		rt->cam->theta -= 360.0;
	else if (rt->cam->theta <= -180.0)
		rt->cam->theta += 360.0;
	if (rt->cam->phi >= 180.0)
		rt->cam->phi -= 360.0;
	else if (rt->cam->phi <= -180.0)
		rt->cam->phi += 360.0;
	basis(rt->cam, rt->cam->phi * (ANG), rt->cam->theta * ANG);
	// get_cam_basis(rt->cam);
}
