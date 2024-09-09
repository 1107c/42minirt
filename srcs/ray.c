/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:12:41 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/09 15:02:49 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"

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
	t_vector	vec;
	t_vector	temp;
	double		theta;
	double		pi;

	vec.x = 0;
	vec.y = cam->orient_vec->y;
	vec.z = cam->orient_vec->z;
	temp.x = 0;
	temp.y = 0;
	temp.z = 1;
	theta = dot_product(&vec, &temp) / sqrt(dot_product(&vec, &vec));
	cam->right_vec->x = 0;
	cam->right_vec->y = theta;
	cam->right_vec->z = -sqrt(1 - theta * theta);
	vec.x = cam->orient_vec->x;
	vec.y = 0;
	pi = dot_product(&vec, &temp) / sqrt(dot_product(&vec, &vec));
	cam->up_vec->x = pi;
	cam->up_vec->y = 0;
	cam->up_vec->z = -sqrt(1 - pi * pi);
	printf("base right vector: %lf, %lf, %lf\n", cam->right_vec->x, cam->right_vec->y, cam->right_vec->z);
	printf("base up vector: %lf, %lf, %lf\n", cam->up_vec->x, cam->up_vec->y, cam->up_vec->z);
}

// void	get_cam_basis(t_cam *cam)
// {
// 	t_vector	v;
// 	t_vector	*u;
// 	int			cnt;

// 	// P(a, b, c), n(p, q, r) => px + qy + rz = d
// 	// d = pa + qb + rc
// 	// 직선의 방정식을
// 	// (x - x') / a' = (y - y') / b' = (z - z') / c'
// 	// => x = a't + x', y = b't + y', z = c't + z'
// 	// (pa'+qb'+rc')t + px'+qy'+rz' = d
// 	// t = (d - (px'+qy'+rz')) / (pa'+qb'+rc')
// 	cnt = 0;
// 	if (cam->orient_vec->x == 0)
// 		cam->right_vec->x= 0;
// 	else
// 	{
// 		v.x = -1;
// 		cnt++;
// 	}
// 	if (cam->orient_vec->y == 0)
// 		v.y = 0;
// 	else
// 	{
// 		v.y = -1;
// 		cnt++;
// 	}
// 	if (cam->orient_vec->z == 0)
// 		v.z = 0;
// 	else
// 	{
// 		v.z = -1;
// 		cnt++;
// 	}
// 	if (cnt == 2)
// 	{
// 		if (v.x == 0)
// 			v.x = cam->coords->x + 1;
// 		else if (v.y == 0)
// 			v.y = cam->coords->y + 1;
// 		else if (v.z == 0)
// 			v.z = cam->coords->z + 1;
// 	}
// 	else if (cnt == 1)
// 	{
// 		if (v.x == 0)
// 		{
// 			v.x = cam->coords->x + 1;
// 			v.y = cam->coords->y;
// 			v.z = cam->coords->z;
// 		}
// 		else if (v.y == 0)
// 		{
// 			v.y = cam->coords->y + 1;
// 			v.x = cam->coords->x;
// 			v.z = cam->coords->z;
// 		}
// 		else if (v.z == 0)
// 		{
// 			v.z = cam->coords->z + 1;
// 			v.x = cam->coords->x;
// 			v.y = cam->coords->y;
// 		}
// 	}
// 	else if (cnt == 0)
// 	{
// 		v.x = cam->coords->x + 1;
// 		v.z = (-(cam->orient_vec->x * v.x + cam->orient_vec->y * v.y) 
// 			+ cam->orient_vec->x * cam->coords->x 
// 			+ cam->orient_vec->y * cam->coords->y
// 			+ cam->orient_vec->z * cam->coords->z)
// 			/ cam->orient_vec->z;
// 	}
// 	printf("base point: %lf, %lf, %lf\n", v.x, v.y, v.z);
// 	v.x -= cam->coords->x;
// 	v.y -= cam->coords->y;
// 	v.z -= cam->coords->z;
// 	normalize_vec(&v);
// 	printf("base right vector: %lf, %lf, %lf\n", v.x , v.y, v.z);
// 	u = cross_product(cam->orient_vec, &v);
// 	normalize_vec(u);
// 	printf("base up vector: %lf, %lf, %lf\n", u->x, u->y, u->z);
// 	cam->right_vec->x = v.x;
// 	cam->right_vec->y = v.y;
// 	cam->right_vec->z = v.z;
// 	cam->up_vec->x = u->x;
// 	cam->up_vec->y = u->y;
// 	cam->up_vec->z = u->z;
// 	cam->corner_vec->x = -(v.x + u->x);
// 	cam->corner_vec->y = -(v.y + u->y);
// 	cam->corner_vec->z = -(v.z + u->z);
// 	normalize_vec(cam->corner_vec);
// }
