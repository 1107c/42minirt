/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:12:41 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/09 16:59:07 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// comment -> yeojukim
// : 이 함수는 카메라 초기화 및 화면의 각 픽셀에 대해 광선을 생성하는 역할을 담당합니다.
// : `u` 는 X축 방향의 정규화된 좌표를 의미하며 `v`는 Y축 방향의 정규화된 좌표를 의미합니다.
// : 여기서 NDC좌표로 변환을 시켜주는 데 NDC란 3D 공간의 객체들을 2D 화면에 매핑하기 위해 사용되는 좌표 체계입니다.
// : -1.0 ~ 1.0의 범위로 표준화를 시켜 일관된 처리를 가능하게 합니다.
// : 매개변수의 x, y는 화면의 좌표를 나타 냅니다. (x = 0 ~ width - 1) (y = 0 ~ height - 1)
/*t_ray	*cam_ray(t_cam *cam, t_rt *rt, double x, double y)
{
	t_ray	*tray;
	double	u;
	double	v;

	tray = malloc(sizeof(tray));
	if (!tray)
		exit(1);
	u = (2.0 * ((x + 0.5) / (double) rt->win_x - 1.0) * cam->fov \
			* (double) rt->win_x / (double) rt->win_y);
	v = (1.0 - 2.0 * ((y + 0.5) / (double) rt->win_y)) * cam->fov;
	tray->origin = cam->coords;
	tray->direction = add_vec(cam->corner_vec, \
			  add_vec(mul_vec(cam->right_vec, u), \
					mul_vec(cam->up_vec, v)));
	tray->direction = sub_vec(tray->direction, cam->coords);
	normalize_vec(tray->direction);
	return (tray);
}*/

// 카메라 시점의 기저벡터를 구하는 과정
// 카메라의 orient_vec의 yz, xz로의 정사영과 z축이 이루는 각 theta, pi를 구한다. 
// 카메라의 orient_vec가 z축 위에 있다고 가정했을 때,
// 해당 벡터를 y축으로 theta만큼, x축으로 pi만큼 회전한 것을 의미한다.
// 축의 회전에 따라 x축, y축도 같이 회전되어 바뀐 벡터를 구해주면
// 이것들이 곧 새로운 시점의 기저벡터들이 된다.
void	get_cam_basis(t_cam *cam)
{
	t_vector	proj_vector_yzx;
	t_vector	z_unit_vector;
	double		theta;

	proj_vector_yzx.x = 0;
	proj_vector_yzx.y = cam->orient_vec.y;
	proj_vector_yzx.z = cam->orient_vec.z;
	z_unit_vector.x = 0;
	z_unit_vector.y = 0;
	z_unit_vector.z = 1;
	theta = dot_product(proj_vector_yzx, z_unit_vector) / \
			sqrt(dot_product(proj_vector_yzx, proj_vector_yzx));
	cam->up_vec.x = 0;
	cam->up_vec.y = theta;
	cam->up_vec.z = -sqrt(1 - theta * theta);
	proj_vector_yzx.x = cam->orient_vec.x;
	proj_vector_yzx.y = 0;
	theta = dot_product(proj_vector_yzx, z_unit_vector) / \
			sqrt(dot_product(proj_vector_yzx, proj_vector_yzx));
	cam->right_vec.x = theta;
	cam->right_vec.y = 0;
	cam->right_vec.z = -sqrt(1 - theta * theta);
	printf("base right vector: %lf, %lf, %lf\n", cam->right_vec.x, cam->right_vec.y, cam->right_vec.z);
	printf("base up vector: %lf, %lf, %lf\n", cam->up_vec.x, cam->up_vec.y, cam->up_vec.z);
}
