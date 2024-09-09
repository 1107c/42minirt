/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:25:49 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/09 15:13:50 by myeochoi         ###   ########.fr       */
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

# define ANG	0.0174533

# define KEY_ESC 65307

# define INT_MAX	2147483647
# define INT_MIN	-2147483648

# define MEM_ALLOC_ERR			"Error\n=> memory allocation failed"
# define FORMAT_ERR				"Error\n=> invalid format"
# define RANGE_ERR				"Error\n=> invalid range"
# define INVALID_OPT			"Error\n=> invalid option"
# define AMB_DUP_ERR			"Error\n=> ambient light duplication error"
# define AMB_LEN_ERR			"Error\n=> invalid ambient light format"
# define AMB_INPUT_ERR			"Error\n=> no amblight input"
# define AMB_RATIO_FORMAT_ERR	"Error\n=> invalid ambient light ratio format"
# define AMB_RATIO_RANGE_ERR	"Error\n=> invalid ambient ratio range"
# define CAM_DUP_ERR			"Error\n=> cam duplication error"
# define CAM_LEN_ERR			"Error\n=> invalid cam format"
# define CAM_INPUT_ERR			"Error\n=> no camera input"
# define CAM_RANGE_ERR			"Error\n=> invalid ambient rgb range"
# define CAM_FOV_FORMAT_ERR		"Error\n=> invalid cam fov format"
# define LIGHT_DUP_ERR			"Error\n=> light duplication error"
# define LIGHT_LEN_ERR			"Error\n=> invalid light format"
# define LIGHT_INPUT_ERR		"Error\n=> no light input"
# define FIG_INPUT_ERR			"Error\n=> no figure input"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# include "../minilibx-linux/mlx.h"
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

// comment -> yeojukim
// : 광선에 대한 정보를 담는 구조체입니다.
// : origin은 광선의 원점(시작점)을 의미하고 direction은 광선의 방향을 의미합니다.
typedef	struct s_ray
{
	t_vector	*origin;
	t_vector	*direction;
}	t_ray;

typedef struct s_amblight
{
	t_vector	*rgb;
	double		light_ratio;
	int		ch;
}	t_amblight;

// comment -> yeojukim
// : coords - 카메라의 위치. 즉, 이 좌표를 기준으로 광선을 계산해야합니다.
// : orient_vec - 방향 벡터. 카메라가 어디를 바라보고있는지를 나타내는 방향 벡터입니다(정면 기준 (0, 0, -1)). z축을 담당합니다.
// : right_vec - 오른쪽 벡터. 카메라 좌우의 기울기를 나타냅니다(정면 기준 (1, 0, 0)). x축을 담당합니다.
// : up_vec - 위쪽 벡터. 카메라 상하의 기울기를 나타냅니다(정면 기준 (0, 1, 0)). y축을 담당합니다.
// : fov - 시야각입니다. 클 수록 넓은 시야를 가지게 됩니다.
// : as_ratio - 화면의 가로 세로 비율입니다. 이 비율에 따라 뷰포트의 높이/너비가 조정됩니다(width / height).
//		fov와 함께 시야를 계산할 때 사용합니다.
// : vp_w, vp_h - 카메라가 볼 수 있는 가상 화면의 너비와 높이를 정의합니다(width * height).
//		값이 클 수록 더 큰 장면을 뷰포트에서 볼 수 있습니다.
// : corner_vec - 뷰포트의 좌하단 모서리 좌표를 나타냅니다. 광선 생성의 기준점으로 사용됩니다.
typedef struct s_cam
{
	t_vector	*coords;
	t_vector	*orient_vec;
	t_vector	*right_vec;
	t_vector	*up_vec;
	double		fov;
	double		as_ratio;
	double		vp_w;
	double		vp_h;
	//int		move_x;
	//int		move_y;
	t_vector	*corner_vec;
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
void	print_err(t_msg	msg, t_rt *rt);
int		open_err(int *arg, char **args, t_rt *rt);

/* init.c */
t_rt		*init_rt();
t_vector	*init_vector();

/* init_utils.c */
t_light	*init_light();
t_fig	*init_fig();

/* close.c */
void	close_all(t_rt *rt, char *error_msg);
void	free_2d_and_close_all(t_rt *rt, char **args, char *msg);

/* draw.c */
void	draw(t_rt *rt);

/* parse.c */
void	parse_data(t_rt *rt);

/* parse_utils.c */
int		ft_iscomma(int c);
int		is_double_range(double d, double range_min, double range_max);
int		is_valid_single_double_value(t_rt *rt, char *arg, double range_min, double range_max);
int		is_valid_multi_double_value(t_vector *vec, char *arg, double range_min, double range_max);
void	*lst_addback(t_rt *rt, t_type type);

/* 2d_array_utils.c */
int		get_arg_len(char **args);
void	print_args(char **args);
void	free_args(char **args);

/* parse_element.c */
void	parse_amb(t_rt *rt, char **args);
void	parse_cam(t_rt *rt, char **args);
void	parse_light(t_rt *rt, char **args);

/* parse_figure.c */
void	parse_plane(t_rt *rt, char **args);
void	parse_sphere(t_rt *rt, char **args);
void	parse_cylinder(t_rt *rt, char **args);

/* rt_utils.c */
void	print_rt(t_rt *rt);

/* key_handle.c */
int	key_handle(int keycode, t_rt *rt);

// comment -> yeojukim
// : 벡터 유틸들의 함수목록들입니다.
/* vector_utils.c */
t_vector	normalize_vec(t_vector *rhs);
double		dot_product(t_vector *lhs, t_vector *rhs);
t_vector	cross_product(t_vector *lhs, t_vector *rhs);
double		udistance_vec(t_vector *lhs, t_vector *rhs);
void		invert_vec(t_vector *rhs);
t_vector	add_vec(t_vector *lhs, t_vector *rhs);
t_vector	sub_vec(t_vector *lhs, t_vector *rhs);
t_vector	mul_vec(t_vector *lhs, double rhs);
// void		cross_product(t_vector *lhs, t_vector *rhs, t_vector *res);
// t_vector	cross_product(t_vector lhs, t_vector rhs);

/* ray.c */
t_ray	*cam_ray(t_cam *cam, t_rt *rt, double x, double y);
void	get_cam_basis(t_cam *cam);

/* intersection.c */
int	intersect_plane(t_fig *plane, t_vector *point, t_vector *cam);
// int	intersect_sphere(t_ray *ray, t_fig *fig);

int	intersect_sphere(t_vector *sphere, t_vector *p1, t_vector *p2, double radius);

#endif
