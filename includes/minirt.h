/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:25:49 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/03 11:12:11 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT
# define MINI_RT

# define PLANE		0
# define SPHERE		1
# define CYLINDER	2

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH	1920
# endif
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT	1080
# endif
# define WINDOW_TITLE	"miniRT"

# define ESC 65307

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>


# include "../minilibx-linux/mlx.h"
# include "math.h"
# include "../libft/libft.h"

typedef enum e_msg
{
	NO_ARG,
	MUCH_ARG,
	EXTEN_ERR,
	FATAL_ERR,
	OPEN_ERR,

}	t_msg;

typedef struct s_amblight
{
	float	light_ratio;
	int		r;
	int		g;
	int		b;
	int		ch;
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
	int		ch;
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
	int		ch;
	struct s_light	*next;
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
	struct s_fig	*next;
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
	char		*file_name;
	int			file_fd;
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