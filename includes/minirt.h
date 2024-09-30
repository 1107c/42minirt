/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:25:49 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/18 11:43:24 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define NUM_THREADS	16

# define V_EPSILON	0.001

# define PLANE		0
# define SPHERE		1
# define CYLINDER	2
# define CONE		3

# define AMBIENT_STRENGTH	0.85
# define DIFFUSE_STRENGTH	0.35
# define SPECULAR_STRENGTH	0.2
# define SHINESS	128.0

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH	1260
# endif
# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT	740
# endif
# define WINDOW_TITLE	"miniRT"

# define ANG	0.0174533

# define KEY_ESC 	65307
# define KEY_UP		65362
# define KEY_DOWN	65364
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_W		119
# define KEY_S		115
# define KEY_A		97
# define KEY_D		100
# define KEY_Q		113
# define KEY_E		101
# define KEY_B		98
# define KEY_N		110
# define KEY_LIGHT	108
# define KEY_PLUS	61
# define KEY_MINUS	45
# define KEY_SPACE	32

# define NUM_UP		65431
# define NUM_DOWN	65433
# define NUM_LEFT	65430
# define NUM_RIGHT	65432
# define NUM_FRONT	65435
# define NUM_BACK	65434
# define NUM_ROT_X	65436
# define NUM_ROT_Y	65429
# define NUM_PLUS	65451
# define NUM_MINUS	65453

# define INT_MAX	2147483647
# define INT_MIN	-2147483648
# define INF		1e13
# define EPSILON	1e-14

# define LIGHT_MAX	10
# define FIG_MAX	50

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
# define FIG_LEN_ERR			"Error\n=> invalid figure format"
# define NORM_VEC_ERR			"Error\n=> not a normalized vector"

# define LIGHT_MAX_ERR			"Error\n=> light maximum count exceeded"
# define FIG_MAX_ERR			"Error\n=> figure maximum count exceeded"

# define NO_HIT					0
# define CENTER_SIDE_HIT			1
# define CENTER_CENTER_HIT		2
# define SIDE_SIDE_HIT			3
# define SIDE_CENTER_HIT			4

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <pthread.h>

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef double			t_mat3[3][3];
typedef struct s_fig	t_fig;

typedef enum e_msg
{
	NO_ARG,
	MUCH_ARG,
	EXTEN_ERR,
	FATAL_ERR,
	OPEN_ERR,
}	t_msg;

typedef enum e_path
{
	PATH_1,
	PATH_2,
	PATH_3,
	PATH_4,
	PATH_5,
	PATH_6,
	PATH_7,
	PATH_8,
	PATH_9,
	PATH_10,
	PATH_11,
	PATH_12,
	PATH_13,
	PATH_14,
	PATH_15,
	PATH_16,
}	t_path;

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

typedef struct s_vec
{
	t_vector	inter_vec;
	t_vector	n_vec;
	t_vector	l_vec;
	t_vector	e_vec;
	t_vector	r_vec;
	t_fig		*fig;
}	t_vec;

typedef struct s_color
{
	t_vector	diffuse_color;
	t_vector	specular_color;
	t_vector	amb;
	t_vector	dif_sum;
	t_vector	spe_sum;
	t_vector	final_color;
	t_vector	save_color;
	t_vector	l_sum;
}	t_color;

typedef struct s_xs
{
	t_vector	from;
	t_vector	ray_dir;
	t_vector	from_fig_center;
	double		abc[3];
	double		t[2];
	double		alpha;
	double		beta;
	double		det;
	double		dn;
	double		ecn;
	double		ecd;
	double		c;
	double		h;
	double		total_dist;
	double		left;
	double		right;
	int			type;
	int			flag;
}	t_xs;

typedef struct s_util
{
	t_vec	vec;
	t_color	color;
	t_xs	xs;
	double	time;
}	t_util;

typedef struct s_amblight
{
	t_vector	rgb;
	double		light_ratio;
	int			cnt;
}	t_amblight;

typedef struct s_cam
{
	t_vector	coords;
	t_vector	orient_vec;
	t_vector	right_vec;
	t_vector	up_vec;
	t_vector	origin_orient_vec;
	t_vector	origin_right_vec;
	t_vector	origin_up_vec;
	t_vector	screen_origin;
	double		fov;
	double		as_ratio;
	double		distance_to_view;
	double		theta;
	double		phi;
	int			cnt;
}	t_cam;

typedef struct s_light
{
	t_vector		xyz;
	t_vector		rgb;
	double			brightness;
	int				is_click;
	struct s_light	*next;
}	t_light;

typedef struct s_bump
{
	t_vector		**normal_map;
	t_vector		**color_map;
	int				normal_height;
	int				normal_width;
	int				save_height;
	int				save_width;
	struct s_bump	*next;
}	t_bump;

typedef struct s_fig
{
	t_vector		xyz;
	t_vector		normal_vec;
	t_vector		rgb;
	t_vector		rgb2;
	t_vector		right_vec;
	t_vector		up_vec;
	int				type;
	double			diameter;
	double			height;
	double			radius_sq;
	int				idx;
	int				is_click;
	int				is_check;
	int				is_bump;
	t_bump			*bump;
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

typedef struct s_rgb {
	char		name[2];
	t_vector	rgb;
}	t_rgb;

typedef struct s_xpm {
	int			info[4];
	t_rgb		colors[256];
	t_vector	**pixels;
}	t_xpm;

typedef struct s_rt
{
	void		*mlx;
	void		*win;
	t_image		*img;
	t_amblight	*amblight;
	t_cam		*cam;
	t_fig		*fig;
	t_light		*light;
	t_fig		*selected;
	t_light		*selected_light;
	t_bump		*bump;
	char		*line;
	char		*error;
	int			file_fd;
	int			light_cnt;
	int			fig_cnt;
	int			bump_cnt;
	int			did_get_normal_map;
	char		**map;
}	t_rt;

typedef struct s_worker
{
	t_rt		*rt;
	int			y_start;
	int			y_end;
	t_util		util;
}	t_worker;

/* error.c */
int			error(char *error_msg);
int			print_err(t_msg	msg);
int			open_file(char *filename);

/* init.c */
t_rt		*init_rt(int fd);

/* init_xss.c */
t_light		*init_light(void);
t_fig		*init_fig(void);
void		init_map(t_rt *rt);
t_bump		*init_bump(void);
t_vector	init_vector(double x, double y, double z);

/* close.c */
void		close_mlx(t_rt *rt);
void		close_all(t_rt *rt, char *error_msg);
void		free_2d_and_close_all(t_rt *rt, char **args, char *msg);
int			close_win(t_rt *rt);

/* draw.c */
void		draw(t_rt *rt);
void		*render_scene(void *worker);
void		clear_image(t_image *img);
void		pixel_to_image(t_image *img, double x, double y, t_vector rgb);

/* parse.c */
void		parse_data(t_rt *rt);

/* parse_utils.c */
int			is_double_range(double d, double range_min, double range_max);
int			is_valid_single_double_value(t_rt *rt, char *arg, double \
range_min, double range_max);
int			is_valid_multi_double_value(t_vector *vec, char *arg, double \
range_min, double range_max);
void		get_fig_idx_vec(t_rt *rt);

/* 2d_array_utils.c */
int			get_arg_len(char **args);
void		print_args(char **args);
void		free_args(char **args);

/* parse_element.c */
void		parse_amb(t_rt *rt, char **args);
void		parse_cam(t_rt *rt, char **args);
void		parse_light(t_rt *rt, char **args);

/* parse_figure.c */
void		parse_plane(t_rt *rt, char **args, int type);
void		parse_sphere(t_rt *rt, char **args, int type);
void		parse_cylinder(t_rt *rt, char **args, int type);

/* print_data.c */
void		print_rt(t_rt *rt);

/* key_handle.c */
int			key_handle(int keycode, t_rt *rt);

// comment -> yeojukim
// : 벡터 유틸들의 함수목록들입니다.
/* vector_utils.c */
t_vector	normalize_vec(t_vector rhs);
double		dot_product(t_vector lhs, t_vector rhs);
t_vector	cross_product(t_vector lhs, t_vector rhs);
double		udistance_vec(t_vector lhs, t_vector rhs);
t_vector	invert_vec(t_vector rhs);
t_vector	add_vec(t_vector lhs, t_vector rhs);
t_vector	sub_vec(t_vector lhs, t_vector rhs);
t_vector	mul_vec(t_vector lhs, double rhs);
int			is_normalized_vec(t_vector vec);
t_vector	init_point(t_cam *cam);

/* intersection.c */
double		intersect_plane(t_fig *pl, t_xs *xs);
double		intersect_sphere(t_fig *sp, t_xs *xs);
double		intersect_cylinder(t_fig *cy, t_xs *xs);
double		intersect_cone(t_fig *cn, t_xs *xs);
void		draw_fig(t_rt *rt, int i, int j);

// void	draw_plane(t_rt *rt);

/* lst_xss.c */
void		*lst_addback(t_rt *rt, t_type type);
void		free_lst(t_rt *rt);
void		free_bump(t_bump *bump);

/* cam_utils.c */
void		set_cam(t_cam *cam);
void		update_basis(t_cam *cam, double phi, double theta);

/* key_handle_2.c */
t_vector	fig_light_translate_module(int move, int dir, t_vector vec);
void		fig_light_translate(int keycode, t_fig *fig, t_light *light);
void		key_light(int keycode, t_rt *rt);
void		fig_rotate(int keycode, t_rt *rt);
void		key_checkboard_bump(int keycode, t_rt *rt);

/* mouse_handle.c */
int			mouse_handle(int keycode, int x, int y, t_rt *rt);

/* get_uv.c */
void		get_cylinder_uv(double uv[2], t_vector point, t_fig *fig);
void		get_plane_uv(double uv[2], t_vector inter_vec, t_fig *fig);
void		get_sphere_uv(double uv[2], t_vector point);
void		get_uv(t_vec *vec, double *uv);

/* draw_utils.c */
void		pixel_to_image(t_image *img, double x, double y, t_vector rgb);

/* get_ray_dist.c */
t_vector	get_cone_normal(t_fig *cn, t_vector p1, t_vector p2, double t);
double		get_ray_dist(t_fig *fig, t_xs *xs);

/* light_and_shadow.c  */
void		add_color(t_color *color, t_fig *fig, t_vec *vec, t_light *tmp);
void		multi_lightning(t_light *light, t_fig *fig, \
	t_util *util, t_amblight *amb);
int			is_in_shadow(t_fig *fig, t_light *light, t_xs *xs, t_vec *vec);

/*	light_and_shadow_utils.c */
t_vector	get_diffuse_color(t_light *lt, t_fig *fig, double power);
t_vector	get_specular_color(t_light *lt, double power);
t_vector	get_light_color(t_vector l_sum, t_light *lt, double power);
void		add_color(t_color *c, t_fig *fig, t_vec *vec, t_light *light);

/* intersect_utils3.c*/
void		get_cn_solution(t_xs *xs);

/* threads.c */
void		init_workers(t_worker *workers, t_rt *rt);
void		thread_work(t_worker *workers);

/* matrix_utils.c */
void		print_mat(t_mat3 a);
void		rotate_matrix(t_mat3 a, double c, double s, t_vector vec);
void		mul_matrix3(t_mat3 a, t_mat3 b);

/* checker.c */
void		checkerboard(t_vec *vec, t_color *color);

/* bump.c */
void		bump(t_worker *wk, t_vec *vec, t_color *color);

/* xs.c */
void		plane_xs(t_fig *pl, t_xs *xs);
void		sphere_xs(t_fig *sp, t_xs *xs);
void		cylinder_xs(t_fig *cy, t_xs *xs);
void		cone_xs(t_fig *cn, t_xs *xs);

/* cy_handler.c */
double		cylinder1(t_fig *cy, t_xs *xs);
double		cylinder2(t_fig *cy, t_xs *xs);
double		cylinder3(t_fig *cy, t_xs *xs);
double		cylinder4(t_fig *cy, t_xs *xs);

/* cy_utils.c */
double		parallel_to_cy_norm(t_fig *cy, t_xs *xs);
t_vector	find_closest_center(t_fig *cy, t_vector from, t_vector ray);
void		get_cy_solution(t_xs *xs);
double		get_cy_up_hit(t_fig *cy, t_xs *xs);

/* cn_utils.c */
double		parallel_to_cn_norm(t_fig *cn, t_xs *xs);
double		cone1(t_fig *cn, t_xs *xs, t_vector close);

/*key_bump.c */
void		key_bump(int keycode, t_rt *rt, t_fig *fig);
t_xpm		*parse_xpm(char *path, t_rt *rt, int i);

/*	xpm_util_1 */
void		skip_xpm(int fd);
void		get_info_xpm(int fd, t_xpm *img);
int			ft_sixteen(char c);
void		get_rgb_xpm(int fd, t_xpm *img);
int			find_color(char *tmp, t_xpm *img, int i, int *j);

/*	xpm_util_2 */
t_vector	**get_normal_map(t_bump *bump, t_rt *rt, char *path, int i);
void		interpret_xpm(int fd, t_xpm *img);
t_vector	**get_height_map(t_xpm *image, double **height_map);
t_vector	**translate_height_to_normal(double **height_map, t_vector \
	**normal_map, int width, int height);
#endif
