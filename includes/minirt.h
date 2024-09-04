/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:39:28 by myeochoi          #+#    #+#             */
/*   Updated: 2024/09/04 14:28:05 by myeochoi         ###   ########.fr       */
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

# define INT_MAX	2147483647
# define INT_MIN	-2147483648

# define MEM_ALLOC_ERR			"Error\n=> memory allocation failed"
# define FORMAT_ERR				"Error\n=> invalid format"
# define RANGE_ERR				"Error\n=> invalid range"
# define INVALID_OPT			"Error\n=> invalid option"
# define AMB_DUP_ERR			"Error\n=> ambient light duplication error"
# define AMB_LEN_ERR			"Error\n=> invalid ambient light format"
# define AMB_RATIO_FORMAT_ERR	"Error\n=> invalid ambient light ratio format"
# define AMB_RATIO_RANGE_ERR	"Error\n=> invalid ambient ratio range"
# define AMB_RATIO_RANGE_ERR	"Error\n=> invalid ambient rgb range"
# define CAM_DUP_ERR			"Error\n=> cam duplication error"
# define CAM_LEN_ERR			"Error\n=> invalid cam format"
# define CAM_RANGE_ERR			"Error\n=> invalid ambient rgb range"
# define CAM_FOV_FORMAT_ERR		"Error\n=> invalid cam fov format"
# define LIGHT_DUP_ERR			"Error\n=> light duplication error"
# define LIGHT_LEN_ERR			"Error\n=> invalid light format"


# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

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

typedef enum e_type
{
	IMG,
	CAM,
	FIG,
	LIGHT,
	AMBLIGHT
}	t_type;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
	char	*error;
}	t_vector;

typedef struct s_amblight
{
	t_vector	*rgb;
	double		light_ratio;
	int		ch;
}	t_amblight;

typedef struct s_cam
{
	t_vector	*xyz;
	t_vector	*orient_vec;
	int		fov;
	int		move_x;
	int		move_y;
	int		ch;
}	t_cam;

typedef struct s_light
{
	t_vector	*xyz;
	t_vector	*rgb;
	double	brightness;
	int		ch;
	struct s_light	*next;
}	t_light;

typedef struct s_fig
{
	t_vector	*xyz;
	t_vector	*normal_vec;
	t_vector	*rgb;
	int		type;
	double	diameter;
	double	height;
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
	char		*line;
	char		*error;
	int			file_fd;
	int			win_x;
	int			win_y;
	void		*mlx;
	void		*win;
}	t_rt;

/* error.c */
int		error(char *error_msg);

/* init.c */
t_rt	*init_rt();

/* close.c */
void	close_all(t_rt *rt, char *error_msg);

/* interpret.c */
void	interpret_data(t_rt *rt);


#endif