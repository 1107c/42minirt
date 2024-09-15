/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsa>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 10:22:56 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/08 10:40:08 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define PLANE 0
# define PLANE_G 4
# define SPHERE	 1
# define SPHERE_G 4
# define CYLINDER 2
# define CYLINDER_G 6
# define TITLE "miniRT"
# define WIDTH 1920
# define HEIGHT 1080
# define BUFFER_SIZE 42

# define INT_MAX 2147483648

# define ACERR "ac wrong."
# define FDERR "fd wrong."
# define PSERR "parse wrong."
# define AMBERR "amb wrong."
# define CAMERR "cam wrong."
# define DBERR "double type wrong."
# define RGERR "range wrong."
# define LIGHTERR "light wrong."
# define OBJERR "obj wrong."
# define INITERR "init wrong."
# define MLXERR "mlx wrong."

# include "minilibx-linux/mlx.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ray
{
	t_vec	ori_vec;
	t_vec	orient_vec;
}	t_ray;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_cam
{
	int	ch;
	t_vec	coords_vec;
	t_vec	orient_vec;
	t_vec	right_vec;
	t_vec	corner_vec;
	int	fov;
	double	as_ratio;
	double	vp_w;
	double	vp_h;
}	t_cam;

typedef struct s_amb
{
	int	ch;
	double	ratio;
	t_color	rgb;
}	t_amb;

typedef struct s_light
{
	t_vec				coords_vec;
	t_color				rgb;
	double				ratio;
	struct s_light		*next;
}	t_light;

typedef struct s_plane
{
	t_vec	coords_vec;
	t_vec	orient_vec;
	t_color	rgb;
}	t_plane;

typedef struct s_sphere
{
	t_vec	coords_vec;
	t_color	rgb;
	float	diameter;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec	coords_vec;
	t_vec	orient_vec;
	t_color	rgb;
	double	diameter;
	double	height;
}	t_cylinder;

typedef struct s_object
{
	int	type;
	int	is_bump;
	int	is_checkboard;
	union u_obj
	{
		t_plane		plane;
		t_sphere	sphere;
		t_cylinder	cylinder;
	}	u_obj;
	struct	s_object	*next;
}	t_object;

typedef struct s_image
{
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}	t_image;

typedef struct s_rt
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		img;
	int			width;
	int			height;
	t_cam		cam;
	t_amb		amb;
	t_object	*obj;
	t_light		*light;
}	t_rt;

/*error*/
int		print_err(char *s);
void		mlx_error(char *s);

/*free*/
void		free_obj(t_object **to);
void		free_light(t_light **tl);
//void		ft_2dfree(char **s);
void		all_free(t_rt *rt);
char		**ft_free(char **s);

/*get_next_line*/
int		get_next_line(int fd, char **line);

/*libft-memorys*/
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *s, int c, size_t n);

/*libft-write*/
void		ft_putendl_fd(char *s, int fd);

/*libft-string change to ...*/
int		ft_coloratoi(char *str);
int		ft_atoi(const char *nptr);
double		ft_stod(char *str);

/*libft-count*/
size_t		ft_strlen(const char *s);
int		ft_gridcount(char **s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);

/*libft_utils*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
int		ft_isdigit(int c);
int		is_double_range(double d, double range_min, double range_max);
char		*ft_strrchr(const char *s, int c);
int		ft_isulong(char *str);

/*init.c*/
void	init_img(t_rt *rt);
void	init_rt(t_rt *rt);

/*set.c*/
int	set_amb(t_rt *rt, char *line);
int	set_cam(t_rt *rt, char *line);
int	set_light(t_rt *rt, char *line);
int	set_obj(t_rt *rt, char *line, int type, int gc);
int	set_plane(t_object *obj, char **tmp);
int	set_sphere(t_object *obj, char **tmp);
int	set_cylinder(t_object *obj, char **tmp);

/*parse.c*/
int		file_check(t_rt *rt, char *av);
int		file_parse(t_rt *rt, int fd);
int		rt_parse(t_rt *rt, char *line);
int		is_double(char *arg);
int		double_parse(char *arg, double *n, double range_min, double range_max);
int		color_parse(t_color *color, char *arg);
int		name_parse(t_rt *rt, char *line);
int		vec_parse(char *line, t_vec *vec);
int		normal_parse(char *line, t_vec *vec, double min, double max);
int		fov_parse(char *line, int *fov, int min, int max);
t_light		*light_memset(t_rt *rt);
void		light_line_up(t_light *tl, t_light **light);
void		obj_line_up(t_object *to, t_object **obj);
t_object	*obj_memset(t_rt *rt, int type);

/*vec_utils*/
double		dot_product(t_vec lhs, t_vec rhs);
t_vec		cross_product(t_vec lhs, t_vec rhs);
t_vec		normalize_vec(t_vec rhs);
t_vec		add_vec(t_vec lhs, t_vec rhs);
t_vec		sub_vec(t_vec lhs, t_vec rhs);
t_vec		mul_vec(t_vec lhs, double rhs);

/*window*/
void		win_button(t_rt *rt);

#endif
