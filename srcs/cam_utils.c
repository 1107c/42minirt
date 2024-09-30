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
static void	get_cam_basis(t_cam *cam);
static t_vector	get_basis_from_matrix(t_mat3 a, t_vector base);

void	set_cam(t_cam *cam, double x, double y)
{
	cam->distance_to_view = WINDOW_WIDTH / \
							(2 * tan(ANG * (cam->fov / 2)));
	cam->origin_orient_vec = cam->orient_vec;
	get_cam_basis(cam);
	cam->origin_right_vec = cam->right_vec;
	cam->origin_up_vec = cam->up_vec;
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

void	update_basis(t_cam *cam, double phi, double theta)
{
	t_mat3	a;
	t_mat3	b;

	update_orient(cam);
	rotate_matrix(a, cos(phi), sin(phi), cam->origin_right_vec);
	rotate_matrix(b, cos(theta), sin(theta), cam->origin_up_vec);
	mul_matrix3(b, a);
	cam->right_vec = get_basis_from_matrix(b, cam->origin_right_vec);
	cam->up_vec = normalize_vec(cross_product(cam->orient_vec, cam->right_vec));
	cam->screen_origin = init_point(cam);
}

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
	new_base = init_vector(mat[0], mat[1], mat[2]);
	return (normalize_vec(new_base));
}
