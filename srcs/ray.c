/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:12:41 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/05 17:15:23 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"

// comment -> yeojukim
// : 이 함수는 카메라 초기화 및 화면의 각 픽셀에 대해 광선을 생성하는 역할을 담당합니다.
// : `u` 는 X축 방향의 정규화된 좌표를 의미하며 `v`는 Y축 방향의 정규화된 좌표를 의미합니다.
// : 여기서 NDC좌표로 변환을 시켜주는 데 NDC란 3D 공간의 객체들을 2D 화면에 매핑하기 위해 사용되는 좌표 체계입니다.
// : -1.0 ~ 1.0의 범위로 표준화를 시켜 일관된 처리를 가능하게 합니다.
// : 매개변수의 x, y는 화면의 좌표를 나타 냅니다. (x = 0 ~ width - 1) (y = 0 ~ height - 1)
t_ray	*cam_ray(t_cam *cam, t_rt *rt, double x, double y)
{
	t_ray	*tray;
	double	u;
	double	v;

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
}

