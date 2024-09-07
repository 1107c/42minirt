/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:02:52 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/07 14:02:52 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// comment -> yeojukim
// : 이 함수는 구체에 대한 광선 물체 교차점 계산입니다.
// : 구는 중심점 (Cx, Cy, Cz)와 반지름 r로 정의됩니다.
// : 구의 표면 위 모든 점(Px, Py, Pz)은 다음 방정식을 따릅니다.
// : [[ (Px - Cx)^2 + (Py - Cy)^2 + (Pz - Cz)^2 = r^2 ]]
// : 광선은 시작점(Ox, Oy, Oz)과 방향 벡터(Dx, Dy, Dz)로 정의됩니다.
// : [[ P(t) = O + t * D ]] -> P(t) = 광선 상의 점.
// : 구의 방정식에 광선의 방정식을 대입하여 교차점이 있는지 찾습니다.
// : [[ (Ox + t * Dx - Cx)^2 + (Oy + t * Dy - Cy)^2 + (Oz + t * Dz - Cz)^2 = r^2 ]]
// : 이 방정식을 풀기 위해 이차방정식의 형태로 바꿉니다.
// : A * t^2 + B * t + C = 0;
// : A = Dx^2 + Dy^2 + Dz^2;
// : B = 2((Ox - Cx)Dx + (Oy - Cy)Dy + (Oz - Cz)Dz);
// : C = (Ox - Cx)^2 + (Oy - Cy)^2 + (Oz - Cz)^2 - r^2;
// : 이차방정식의 해를 구하기 위해 판별식을 계산합니다.
// : @ = B^2 - 4AC;
// : @가 0일 시 정확히 한 점에서 접합니다. 0 보다 클 시 두 점에서 교차합니다. 0 보다 작을 시 교차하지 않습니다.
// : 교차점(t)의 위치를 구하기 위해 이차방정식 근의 공식을 사용합니다.
// : t = (-B +- sqrt(@) / (2A));
// : 두개의 해 모두 교차점의 매개변수이지만 양수일 때만 해당 값을 사용합니다.
double	intersect_sphere(t_ray ray, t_fig *fig)
{
	t_vector	*tvec;
	double	abc[3];
	double	disc;
	double	t[2];

	tvec = sub_vec(ray.origin, fig->xyz);

	abc[0] = dot_product(ray.direction, ray.direction);
	abc[1] = 2.0 * dot_product(tvec, ray.direction);
	abc[2] = dot_product(tvec, tvec) - (fig->diameter * fig->diameter);
	
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];

	if (disc < 0)
		return (-1.0);

	t[0] = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	t[1] = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);

	if (t[0] > 0 && t[0] < t[1])
		return (t[0]);
	if (t[1] > 0)
		return (t[1]);
	return (-1.0);
}
