/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:25:49 by ksuh              #+#    #+#             */
/*   Updated: 2024/07/04 13:23:13 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT
# define MINI_RT

# define PLANE		0
# define SPHERE		1
# define CYLINDER	2

# define WINDOW_WIDTH	1920
# define WINDOW_HEIGHT	1080
# define WINDOW_TITLE	"miniRT"

# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include "math.h"
# include "libft/libft.h"

typedef struct s_amblight
{
	float	light_ratio;
	int		r;
	int		g;
	int		b;
}	t_amblight;

typedef struct s_cam
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	int		fov;
	int		move_x;
	int		move_y;
}	t_cam;

typedef struct s_light
{
	float	x;
	float	y;
	float	z;
	float	brightness;
	int		r;
	int		g;
	int		b;	
}	t_light;

typedef struct s_fig
{
	int		type;
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	float	diameter;
	float	height;
	int		r;
	int		g;
	int		b;	
}	t_fig;

typedef struct s_image
{
	void	*img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*buffer;
}	t_image;

typedef struct s_rt
{
	t_image		*img;
	t_cam		*cam;
	t_fig		*fig;
	t_light		*light;
	t_amblight	*amblight;
	int			win_x;
	int			win_y;
	void		*mlx;
	void		*win;
}	t_rt;

/* error.c */
int		error(int error_num);

/* init.c */
t_rt	*init_rt();

/* close.c */
void	close_all(t_rt *rt, int error_num);

#endif