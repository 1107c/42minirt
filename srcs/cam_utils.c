/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:43:32 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/16 06:24:37 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	update_orient(t_cam *cam);
// static t_ray	get_cam_ray(t_cam *cam);

void	set_cam(t_cam *cam, double x, double y)
{
	cam->distance_to_view = WINDOW_WIDTH / \
							(2 * tan(ANG * (cam->fov / 2)));
	cam->origin_orient_vec = cam->orient_vec;
	get_cam_basis(cam);
	cam->origin_right_vec = cam->right_vec;
	cam->origin_up_vec = cam->up_vec;
}

// 카메라 시점의 기저벡터를 구하는 과정
// 카메라의 orient_vec의 yz, xz로의 정사영과 z축이 이루는 각 theta, pi를 구한다.
// 카메라의 orient_vec가 z축 위에 있다고 가정했을 때,
// 해당 벡터를 y축으로 theta만큼, x축으로 pi만큼 회전한 것을 의미한다.
// 축의 회전에 따라 x축, y축도 같이 회전되어 바뀐 벡터를 구해주면
// 이것들이 곧 새로운 시점의 기저벡터들이 된다.

// t_vector	proj_vector_yzx;
// t_vector	z_unit_vector;
// double		theta;

// proj_vector_yzx = (t_vector) {0, cam->orient_vec.y, cam->orient_vec.z, 0};
// z_unit_vector = (t_vector) {0, 0, 1, 0};
// theta = dot_product(proj_vector_yzx, z_unit_vector) /
// 		sqrt(dot_product(proj_vector_yzx, proj_vector_yzx));
// cam->up_vec = (t_vector) {0, theta, -sqrt(1 - theta * theta), 0};
// proj_vector_yzx.x = cam->orient_vec.x;
// proj_vector_yzx.y = 0;
// theta = dot_product(proj_vector_yzx, z_unit_vector) /
// 		sqrt(dot_product(proj_vector_yzx, proj_vector_yzx));
// cam->right_vec = (t_vector) {theta, 0, -sqrt(1 - theta * theta), 0};

void	copy_matrix3(t_mat3 a, t_mat3 b)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			a[i][j] = b[i][j];
	}
}

void	mul_matrix3(t_mat3 a, t_mat3 b)
{
	t_mat3	c;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			k = -1;
			c[i][j] = 0;
			while (++k < 3)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
	copy_matrix3(a, c);
}

void	rot_matrix(t_mat3 a, double angle, t_vector vec)
{
	a[0][0] = cos(angle) + pow(vec.x, 2) * (1 - cos(angle));
	a[0][1] = vec.x * vec.y * (1 - cos(angle)) - vec.z * sin(angle);
	a[0][2] = vec.x * vec.z * (1 - cos(angle)) + vec.y * sin(angle);;
	a[1][0] = vec.y * vec.x * (1 - cos(angle)) + vec.z * sin(angle);;
	a[1][1] = cos(angle) + pow(vec.y, 2) * (1 - cos(angle));
	a[1][2] = vec.y * vec.z * (1 - cos(angle)) - vec.x * sin(angle);
	a[2][0] = vec.z * vec.x * (1 - cos(angle)) - vec.y * sin(angle);;
	a[2][1] = vec.z * vec.y * (1 - cos(angle)) + vec.x * sin(angle);;
	a[2][2] = cos(angle) + pow(vec.z, 2) * (1 - cos(angle));
}

// void	init_yz(t_mat3 a, double angle)
// {
// 	a[0][0] = 1;
// 	a[0][1] = 0;
// 	a[0][2] = 0;
// 	a[1][0] = 0;
// 	a[1][1] = cos(angle);
// 	a[1][2] = -sin(angle);
// 	a[2][0] = 0;
// 	a[2][1] = sin(angle);
// 	a[2][2] = cos(angle);
// }

// void	init_zx(t_mat3 a, double angle)
// {
// 	a[0][0] = cos(angle);
// 	a[0][1] = 0;
// 	a[0][2] = sin(angle);
// 	a[1][0] = 0;
// 	a[1][1] = 1;
// 	a[1][2] = 0;
// 	a[2][0] = -sin(angle);
// 	a[2][1] = 0;
// 	a[2][2] = cos(angle);
// }

t_vector	get_basis_from_matrix(t_mat3 a, t_vector base)
{
	t_vector	new_base;
	double		mat[3];
	double		mat1[3];
	int			i;
	int			j;

	ft_bzero(mat, sizeof(mat));
	i = -1;
	mat1[0] = base.x;
	mat1[1] = base.y;
	mat1[2] = base.z;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			mat[i] += a[i][j] * mat1[j];
	}
	new_base.x = mat[0];
	new_base.y = mat[1];
	new_base.z = mat[2];
	return (normalize_vec(new_base));
}

void	print_mat(t_mat3 a)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			printf("%lf ", a[i][j]);
		printf("\n");
	}
	printf("\n");
}



void	basis(t_cam *cam, double phi, double theta)
{
	t_mat3	a;
	t_mat3	b;

	update_orient(cam);
	rot_matrix(a, phi, cam->origin_right_vec);
	rot_matrix(b, theta, cam->origin_up_vec);
	mul_matrix3(b, a);
	cam->right_vec = get_basis_from_matrix(b, cam->origin_right_vec);
	cam->up_vec = normalize_vec(cross_product(cam->orient_vec, cam->right_vec));
	cam->screen_origin = init_point(cam);
	// printf("phi, theta: %lf %lf\n", cam->phi, cam->theta);
	// printf("orient: %lf %lf %lf\n", cam->orient_vec.x, cam->orient_vec.y, cam->orient_vec.z);
	// printf("right: %lf %lf %lf\n", cam->right_vec.x, cam->right_vec.y, cam->right_vec.z);
	// printf("up: %lf %lf %lf\n", cam->up_vec.x, cam->up_vec.y, cam->up_vec.z);
}

void	get_cam_basis(t_cam *cam)
{
	t_vector	y_unit_vector;

	update_orient(cam);
	if (fabs(cam->orient_vec.y) != 1)
		y_unit_vector = (t_vector){0, 1, 0, 0};
	else
		y_unit_vector = (t_vector){0, 0, 1, 0};
	cam->right_vec = cross_product(y_unit_vector, cam->orient_vec);
	cam->right_vec = normalize_vec(cam->right_vec);
	cam->up_vec = cross_product(cam->orient_vec, cam->right_vec);
	cam->up_vec = normalize_vec(cam->up_vec);
	cam->screen_origin = init_point(cam);
	// printf("phi, theta: %lf %lf\n", cam->phi, cam->theta);
	// printf("orient: %lf %lf %lf\n", cam->orient_vec.x, cam->orient_vec.y, cam->orient_vec.z);
	// printf("right: %lf %lf %lf\n", cam->right_vec.x, cam->right_vec.y, cam->right_vec.z);
	// printf("up: %lf %lf %lf\n", cam->up_vec.x, cam->up_vec.y, cam->up_vec.z);
}

void	update_orient(t_cam *cam)
{
	cam->orient_vec = add_vec(mul_vec(cam->origin_orient_vec, \
		cos(ANG * cam->phi) * cos(ANG * cam->theta)), \
		mul_vec(cam->origin_right_vec, \
		cos(ANG * cam->phi) * sin(ANG * cam->theta)));
	cam->orient_vec = add_vec(cam->orient_vec, \
		mul_vec(cam->origin_up_vec, sin(ANG * cam->phi)));
	cam->orient_vec = normalize_vec(cam->orient_vec);
}
