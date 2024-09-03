/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:25:49 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/02 14:00:27 by ksuh             ###   ########.fr       */
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

# define KEY_ESC	65307

# define KEY_PLUS	61
# define KEY_MINUS	45

# define KEY_R		114

# define KEY_W		119
# define KEY_S		115
# define KEY_A		97
# define KEY_D		100

# define KEY_Q		113
# define KEY_E		101

# define KEY_Z		122
# define KEY_X		120

# define KEY_I		105
# define KEY_P		112

# define KEY_UP		65362
# define KEY_DOWN	65364
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

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
	t_image		*img;	// mlx_image 
	t_cam		*cam;	// camera
	t_fig		*fig;	// figure
	t_light		*light;	// light
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

/* key_handle.c */
int	key_handle(int keycode, t_rt *rt);

/* draw.c */
void	draw(t_rt *rt);

#endif