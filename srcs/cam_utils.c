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
	//printf("set cam: %lf, %lf\n", x, y);
	cam->distance_to_view = WINDOW_WIDTH / \
							(2 * tan(ANG * (cam->fov / 2)));
	//printf("dist: %lf\n", cam->distance_to_view);
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
void	get_cam_basis(t_cam *cam)
{
	t_vector	y_unit_vector;
	t_vector	z_inv;
	t_vector	inv_right;

	update_orient(cam);
	if (fabs(cam->orient_vec.y) != 1)
		y_unit_vector = (t_vector){0, 1, 0, 0};
	else
		y_unit_vector = (t_vector){0, 0, -1, 0};
	z_inv = cam->orient_vec;
	// printf("orient vector: %lf, %lf, %lf\n", \
			cam->orient_vec.x, cam->orient_vec.y, cam->orient_vec.z);
	cam->right_vec = cross_product(y_unit_vector, z_inv);
	cam->up_vec = cross_product(z_inv, cam->right_vec);
	// printf("base right vector: %lf, %lf, %lf\n", \
			cam->right_vec.x, cam->right_vec.y, cam->right_vec.z);
	// printf("base up vector: %lf, %lf, %lf\n", \
			cam->up_vec.x, cam->up_vec.y, cam->up_vec.z);
	inv_right = invert_vec(cam->right_vec);
	cam->corner_vec = sub_vec(inv_right, cam->up_vec);
	//cam->ray = get_cam_ray(cam);
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
	//printf("%lf %lf\n", cam->phi, cam->theta);
	// printf("orient vector: %lf, %lf, %lf\n",
		// cam->orient_vec.x, cam->orient_vec.y, cam->orient_vec.z);
}
