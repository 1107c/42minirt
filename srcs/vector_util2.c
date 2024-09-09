/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:21:50 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/05 14:21:50 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// comment -> yeojukim
// : 두 벡터의 합을 도출합니다.
// : 이 함수는 광선-표면 교차 지점을 찾거나 광선의 경로를 추적할 때 사용합니다(뺄셈도 동일한 역할을 수행함).
t_vector	*add_vec(t_vector *lhs, t_vector *rhs)
{
	t_vector	*res;

	res = malloc(sizeof(res));
	res->x = lhs->x + rhs->x;
	res->y = lhs->y + rhs->y;
	res->z = lhs->z + rhs->z;

	return (res);
}

// comment -> yeojukim
// : 두 벡터의 차를 도출합니다.
t_vector	*sub_vec(t_vector *lhs, t_vector *rhs)
{
	t_vector	*res;

	res = malloc(sizeof(res));
	res->x = lhs->x - rhs->x;
	res->y = lhs->y - rhs->y;
	res->z = lhs->z - rhs->z;

	return (res);
}

// comment -> yeojukim
// : 벡터의 각 구성 요소에 스칼라를 곱합니다.
// : 광선 위치와 방향, 벡터 길이, 빛의 강도를 스케일링할 때 사용됩니다.
t_vector	*mul_vec(t_vector *lhs, double rhs)
{
	t_vector	*res;

	res = malloc(sizeof(res));
	res->x = lhs->x * rhs;
	res->y = lhs->y * rhs;
	res->z = lhs->z * rhs;

	return (res);
}
