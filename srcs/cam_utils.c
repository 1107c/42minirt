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
	cam->right_vec = cross_product(y_unit_vector, z_inv);
	cam->up_vec = cross_product(z_inv, cam->right_vec);
	inv_right = invert_vec(cam->right_vec);
	cam->corner_vec = sub_vec(inv_right, cam->up_vec);
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

// comment -> yeojukim
// : 이 함수는 카메라 초기화 및 화면의 각 픽셀에 대해 광선을 생성하는 역할을 담당합니다.
// : `u` 는 X축 방향의 정규화된 좌표를 의미하며 `v`는 Y축 방향의 정규화된 좌표를 의미합니다.
// : 여기서 NDC좌표로 변환을 시켜주는 데 NDC란 3D 공간의 객체들을 2D 화면에 매핑하기 위해 사용되는 좌표 체계입니다.
// : -1.0 ~ 1.0의 범위로 표준화를 시켜 일관된 처리를 가능하게 합니다.
// : 매개변수의 x, y는 화면의 좌표를 나타 냅니다. (x = 0 ~ width - 1) (y = 0 ~ height - 1)

/*
t_ray	cam_ray(t_cam *cam, t_rt *rt, double x, double y)
{
	t_ray	ray;
	t_vector	vec;
	double	vh;
	double	vw;
	double	u;
	double	v;

	ray.origin = cam->coords;
	vh = 2.0 * tan(cam->fov * ANG / 2.0);
	vw = vh * 16 / 9;
	u = (x + 0.5) / (double) WINDOW_WIDTH;
	v = (y + 0.5) / (double) WINDOW_HEIGHT;
	double screen_x = (2.0 * u - 1.0) * vw;
	double screen_y = (1.0 - 2.0 * v) * vh;
	// printf("screen_x, screen_y: %lf %lf %lf %lf\n", vw, vh, screen_x, screen_y);
	vec = add_vec(add_vec(mul_vec(cam->right_vec, screen_x), \
			mul_vec(cam->up_vec, screen_y)), \
			cam->orient_vec);
	ray.direction = normalize_vec(vec);
	// u = (2.0 * ((x + 0.5) / (double) rt->win_x - 1.0) * cam->fov \
	// 		* (double) rt->win_x / (double) rt->win_y);
	// v = (1.0 - 2.0 * ((y + 0.5) / (double) rt->win_y)) * cam->fov;
	// tray.origin = cam->coords;
	// tray.direction = add_vec(cam->corner_vec, \
	// 		  add_vec(mul_vec(cam->right_vec, u), \
	// 				mul_vec(cam->up_vec, v)));
	// tray.direction = sub_vec(tray.direction, cam->coords);
	// normalize_vec(tray.direction);

	return (ray);
}

t_ray	get_cam_ray(t_cam *cam)
{
	t_ray	tray;
	double	u;
	double	v;

	u = 2.0 * cam->fov / WINDOW_HEIGHT;
	v = -2.0 * cam->fov / WINDOW_HEIGHT;
	printf("ray u, v: %lf, %lf\n", u, v);
	tray.u = mul_vec(cam->right_vec, u);
	tray.v = mul_vec(cam->up_vec, v);
	u = cam->fov * (-2.0 * WINDOW_WIDTH + 1.0) / WINDOW_HEIGHT;
	v = cam->fov * (1.0 - 1.0 / WINDOW_HEIGHT);
	printf("u, v: %lf, %lf\n", u, v);
	tray.origin = cam->coords;
	tray.direction = add_vec(add_vec(mul_vec(cam->right_vec, u), \
					mul_vec(cam->up_vec, v)), \
					cam->corner_vec);
	tray.direction = sub_vec(tray.direction, cam->coords);
	tray.unit = normalize_vec(tray.direction);
	printf("unit: %lf %lf %lf\n", tray.unit.x, tray.unit.y, tray.unit.z);
	tray.save = tray.direction;
	return (tray);
}
*/

void	update_ray(t_ray *ray, int right)
{
	if (right)
		ray->direction = add_vec(ray->direction, ray->u);
	else
	{
		ray->save = sub_vec(ray->save, ray->v);
		ray->direction = ray->save;
	}
	ray->unit = normalize_vec(ray->direction);
}

// bump맵 판별하는 변수
// checker ;;