/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:08:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/19 14:32:29 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>

// 두 점 P(a, b, c), P'(a', b', c')을 지나는 직선의 방정식은 다음과 같다.
// (x - a) / (a' - a) = (y - b) / (b' - b) = (z - c) / (c' - c)		---- *1

// 한 점 P''(a'', b'', c'')을 지나고, 법선벡터가 n(p, q, r)인 평면의 방정식:
// px + qy + rz = pa'' + qb'' + rc''								---- *2

// *1 = t로 두고 x, y, z를 매개변수 t로 치환하면 (0 < t, P(a, b, c)가 카메라의 위치이기 때문)
// x = (a' - a)t + a
// y = (b' - b)t + b
// z = (c' - c)t + c

// 직선상의 점 P''(x, y, z) 가 평면위에 있어야할 조건을 구해본다면
// p((a' - a)t + a) + q((b' - b)t + b) + r((c' - c)t + c) = pa'' + qb'' + rc''
// (p(a' - a) + q(b' - b) + r(c' - c))t = (pa'' + qb'' + rc'') - (pa + qb + rc)
// i) p(a' - a) + q(b' - b) + r(c' - c) = 0
// 우변 = 0이면 모든 t에 대해 식이 성립 o
// 우변 != 0이면 모든 t에 대해 식이 성립 x
// ii) p(a' - a) + q(b' - b) + r(c' - c) != 0
// ((pa'' + qb'' + rc'') - (pa + qb + rc)) / p(a' - a) + q(b' - b) + r(c' - c) > 0이면
// 카메라 시야에서 평면과 교점이 발생

// double	intersect_plane(t_fig *pl, t_ray ray)
// {
// 	double		d;
// 	double		res;

// 	d = dot_product(pl->normal_vec, pl->xyz)
// 		- dot_product(pl->normal_vec, ray.origin);
// 	res = dot_product(pl->normal_vec, ray.direction);
// 	if (res == 0)
// 	{
// 		if (d == 0)
// 			return (0.0);
// 		return (-1.0);
// 	}
// 	return (d / res);
// }

double	intersect_plane(t_fig *pl, t_vector cam, t_vector point)
{
	t_vector	vec;
	double		d;
	double		res;

	vec = sub_vec(point, cam);
	d = dot_product(pl->normal_vec, pl->xyz) \
		- dot_product(pl->normal_vec, cam);
	res = dot_product(pl->normal_vec, vec);
	if (fabs(res) <= EPSILON)
	{
		if (fabs(d) <= EPSILON)
			return (0.0);
		return (-1.0);
	}
	return (d / res);
}

// 두 점 P(a, b, c), P'(a', b', c')을 지나는 직선의 방정식
// (x - a) / (a' - a) = (y - b) / (b' - b) = (z - c) / (c' - c)		---- *1

// 반지름의 길이가 r이고 중심이 C(a'', b'' c'')인 구의 방정식
// (x - a'')**2 + (y - b'')**2 + (z - c'')**2 = r**2				---- *2

// 위와 마찬가지로 직선상의 점 P''(x, y, z)를 *1=t로 치환한 값을 *2에 대입하면
// (t(a' - a) + (a - a''))**2 +
// (t(b' - b) + (b - b''))**2 +
// (t(c' - c) + (c - c''))**2 - r**2 = 0
// t*t의 계수(X): (a' - a)**2 + (b' - b)**2 + (c' - c)**2
// t의 계수(Y): 2((a' - a)(a - a'') + (b' - b)(b - b'') + (c' - c)(c - c''))
// 상수항의 계수(Z): (a - a'')**2 + (b - b'')**2 + (c - c'')**2 - r**2
// t의 관한 이차방정식의 해가 존재할 조건은
// D/4 >= 0 => Y**2 - XZ >= 0

double	intersect_sphere(t_fig *sp, t_vector p1, t_vector p2)
{
	t_vector	vec1;
	t_vector	vec2;
	double		det[3];
	double		res;
	double		t[2];

	vec1 = sub_vec(p2, p1);
	vec2 = sub_vec(p1, sp->xyz);
	det[0] = dot_product(vec1, vec1);
	det[1] = dot_product(vec1, vec2);
	det[2] = dot_product(vec2, vec2) - sp->diameter * sp->diameter / 4;
	res = det[1] * det[1] - det[0] * det[2];
	if (fabs(res) > EPSILON && res < 0)
		return (-1.0);
	t[0] = (-det[1] - sqrt(res)) / det[0];
	t[1] = (-det[1] + sqrt(res)) / det[0];
	if (t[0] > 0 && t[0] < t[1])
		return (t[0]);
	if (t[1] > 0)
		return (t[1]);
	return (-1.0);
}
// t[0] = (-det[1] + sqrt(res)) / det[0];
// alpha = t[0] * dn + ecn;
// beta = alpha - t[0] * dn;
// t[1] = (-det[1] - sqrt(res)) / det[0];
// beta += t[1] * dn;

double	intersect_cylinder(t_fig *cy, t_vector p1, t_vector p2, int *flg)
{
	t_util		util;

	util = init_cy_util(cy, p1, p2);
	if (fabs(util.abc[0]) < EPSILON && fabs(util.abc[1]) < EPSILON)
		return (parallel_to_cy_norm(util, cy, p1, p2));
	if (util.det < 0)
		return (-1.0);
	get_cy_solution(&util, cy);
	if ((util.alpha < 0 && util.beta < 0) \
		|| (util.alpha > cy->height && util.beta > cy->height) \
		|| (util.t[0] <= 0 && util.t[1] <= 0))
		return (-1.0);
	if ((util.t[0] > 0 && util.t[1] > 0))
		return (handle_cy_positive(util, cy, flg));
	*flg = 1;
	if (util.t[0] >= 0)
		return (util.t[0]);
	return (util.t[1]);
}
/*
det[0] = (cy->height * cy->height * \
		(dot_product(vec1, vec1) - dn * dn)) - \
		(cy->diameter * cy->diameter * dn * dn / 4);
det[1] = (cy->height * cy->height * (ecd - ecn * dn)) - \
		(cy->diameter * cy->diameter * dn * (ecn - cy->height) / 4);
det[2] = cy->height * cy->height * (dot_product(vec2, vec2) - \
		ecn * ecn - cy->diameter * cy->diameter / 4) - \
		cy->diameter * cy->diameter * (ecn * ecn + cy->height * cy->height - \
		2 * cy->height * ecn) / 4;
*/
double	intersect_cone(t_fig *cn, t_vector p1, t_vector p2)
{
	t_util	util;

	util = init_cn_util(cn, p1, p2);
	// if (fabs(util.abc[0]) < EPSILON && fabs(util.abc[1] < EPSILON))
	if (util.det < 0)
		return (-1.0);
	get_cn_solution(&util);
	if ((util.alpha < 0 && util.beta < 0) || \
		(util.alpha > cn->height && util.beta > cn->height) || \
		(util.t[0] <= 0 && util.t[1] <= 0))
		return (-1.0);
	if ((util.t[0] > 0 && util.t[1] > 0))
		return (handle_cn_positive(util, cn));
	// return (-1.0);
	// printf("t: %lf, %lf\n", util.t[0], util.t[1]);
	if (util.t[0] >= 0)
		return (util.t[0]);
	// return (-1.0);
	return (util.t[1]);
}
