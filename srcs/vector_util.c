/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:53:53 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/05 10:53:53 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// comment -> yeojukim
// : 이 함수는 벡터의 정규화를 담당하고있습니다. 벡터의 크기를 1로 만들면서 방향을 유지시켜 줍니다.
// : 계산의 단순화와 이로 인해 생기는 안정성을 높이기 위해 만들었습니다.
t_vector	normalize_vec(t_vector v)
{
	double	l;

	l = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (l != 0)
	{
		v.x /= l;
		v.y /= l;
		v.z /= l;
	}
	return (v);
}

// comment -> yeojukim
// : 이 함수는 두 벡터 사이의 각도를 계산 하는데 사용되는 내적입니다.
// : 광원과 조명을 계산하기 위해 사용됩니다.
double	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v1.z);
}

// comment -> yeojukim
// : 이 함수는 두 벡터에 모두 수직인 새로운 벡터를 생성하는데 사용되는 외적입니다.
// : 법선 벡터를 계산 혹은 면의 방향을 결정하는데 유용합니다.
t_vector	cross_product(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;

	return (res);
}

// comment -> yeojukim
// : 이 함수는 두 벡터 사이의 유클리드 거리를 계산하여, 어떤 물체가 더 가까운지,
//	광원에서 표면까지의 거리가 얼마나 되는지를 구합니다.
// : 레이트레이싱에서 교차점과의 거리 계산, 조명 효과 등을 구현하기 위한 함수입니다.
double	udistance_vec(t_vector v1, t_vector v2)
{
	double	dx;
	double	dy;
	double	dz;

	dx = v1.x - v2.x;
	dy = v1.y - v2.y;
	dz = v1.z - v2.z;

	return (sqrt(dx * dx + dy * dy + dz * dz));
}

// comment -> yeojukim
// : 이 함수는 벡터를 반전 시킵니다.
// : 그림자 계산을 할 때 사용합니다.
void	invert_vec(t_vector v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.x;
}
