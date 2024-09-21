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

static double	get_traingle_height(t_fig *cy, t_vector point);
static t_vector	get_point(t_vector p1, t_vector p2, double t);

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

// a', b', c' => 실린더의 center점(CY)
// a'', b'', c'' => 실린더의 normal_vec(CYN)
// a, b, c => 카메라의 위치(C)
// p, q, r => 카메라의 ray의 방향벡터(CN)
// A = dot_product(CYN, CN)
// B = -dot_product(CN, CN)
// C = dot_product(CYN, CYN)
// D = -dot_product(A)
// E = dot_product(C - CY, CN)
// F = dot_product(C - CY, CYN)

double	find_eqution(t_fig *cy, t_util util, double small, double big)
{
	double		c;
	double		tanh;
	double		h;
	double		x;

	c = dot_product(util.ray_dir, cy->normal_vec) \
		/ sqrt(dot_product(util.ray_dir, util.ray_dir));
	if (c < 0)
		c = -c;
	tanh = sqrt(1 - c * c) / c;
	h = get_traingle_height(cy, get_point(util.origin, util.ray_dir, small));
	x = cy->diameter / tanh;
	return (big * h / x + small * (x - h) / x);
}

t_vector	get_point(t_vector p1, t_vector p2, double t)
{
	t_vector	p;

	p = add_vec(p1, mul_vec(p2, t));
	return (p);
}

double	get_traingle_height(t_fig *cy, t_vector point)
{
	t_vector	top;
	t_vector	bottom;
	t_vector	tmp[2];
	double		t[2];
	double		c;

	bottom = cy->xyz;
	top = add_vec(cy->xyz, mul_vec(cy->normal_vec, cy->height));
	tmp[0] = sub_vec(top, point);
	t[0] = sqrt(dot_product(tmp[0], tmp[0]));
	tmp[1] = sub_vec(bottom, point);
	t[1] = sqrt(dot_product(tmp[0], tmp[1]));
	if (t[0] <= t[1])
		c = dot_product(cy->normal_vec, tmp[0]) / t[0];
	else
		c = dot_product(cy->normal_vec, tmp[1]) / t[1];
	if (c < 0)
		c = -c;
	if (t[0] <= t[1])
		return (t[0] * c);
	return (t[1] * c);
}

t_vector  get_closest_center(t_fig *cy, t_vector point)
{
   	t_vector	top;
	t_vector	bottom;
    t_vector    t[2];
	double		dist[2];

	bottom = cy->xyz;
	top = add_vec(cy->xyz, mul_vec(cy->normal_vec, cy->height));
	t[0] = sub_vec(bottom, point);
	t[1] = sub_vec(top, point);
	dist[0] = dot_product(t[0], t[0]);
	dist[1] = dot_product(t[1], t[1]);
	if (dist[0] < dist[1])
	   return (bottom);
	return (top);
}

double  get_parallel_norm_hit(t_fig *cy, t_vector point, t_vector end)
{
	t_vector	closer_area;
	t_vector	t[2];
	double		height;
	double		total_dist;

	closer_area = get_closest_center(cy, point);
	t[0] = sub_vec(closer_area, point);
	height = fabs(dot_product(t[0], cy->normal_vec));
	t[1] = sub_vec(end, point);
	total_dist = sqrt(dot_product(t[1], t[1]));
	return (height / total_dist);
}

// dist = dot_product(vec2, vec3) / sqrt(dot_product(vec3, vec3));
// if (dist < 0)
// 	dist = -dist;
// res = dot_product(vec1, cy->normal_vec) / dot_product(vec1, vec1);
// if ((res == 1 || res == -1) && dist <= cy->diameter / 2)
// 	return (get_parallel_norm_hit(cy, p1, p2));

// vec1 = sub_vec(p2, p1); // d
// vec2 = sub_vec(p1, cy->xyz); // e - c
// vec3 = cross_product(vec1, cy->normal_vec);
// dn = dot_product(vec1, cy->normal_vec);
// det[0] = dot_product(vec1, vec1) - dn * dn;
// det[1] = dot_product(vec1, vec2) - dot_product(vec2, cy->normal_vec) * dn;
// det[2] = dot_product(vec2, vec2) - dot_product(vec2, cy->normal_vec) *
// 		dot_product(vec2, cy->normal_vec) - (cy->diameter * cy->diameter) / 4;

t_util	init_cy_util(t_fig *cy, t_vector p1, t_vector p2)
{
	t_util	util;

	util.origin = p1;
	util.ray_dir = sub_vec(p2, p1);
	util.from_fig_center = sub_vec(p1, cy->xyz); // ec
	util.dn = dot_product(util.ray_dir, cy->normal_vec);
	util.abc[0] = dot_product(util.ray_dir, util.ray_dir) - util.dn * util.dn;
	util.abc[1] = dot_product(util.ray_dir, util.from_fig_center) \
				- dot_product(util.from_fig_center, cy->normal_vec) * util.dn;
	util.abc[2] = dot_product(util.from_fig_center, util.from_fig_center) \
				- dot_product(util.from_fig_center, cy->normal_vec) \
				* dot_product(util.from_fig_center, cy->normal_vec) \
				- (cy->diameter * cy->diameter) / 4;
	util.det = util.abc[1] * util.abc[1] - util.abc[0] * util.abc[2];
	return (util);
}

// dn = dot_product(vec1, cy->normal_vec);
// ecn = dot_product(cy->normal_vec, vec2);
// ecd = dot_product(vec1, vec2);
// det[0] = dot_product(vec1, vec1) - (1 + pow(cy->diameter / 2, 2) / pow(cy->height, 2)) * pow(dn, 2);
// det[1] = ecd + (pow(cy->diameter / 2, 2) / cy->height) * dn
// 		- (1 + pow(cy->diameter / 2, 2) / pow(cy->height, 2)) * ecn * dn;
// det[2] = dot_product(vec2, vec2) + 2 * (pow(cy->diameter / 2, 2) / cy->height) * ecn
// 		- (1 + pow(cy->diameter / 2, 2) / pow(cy->height, 2)) * pow(ecn, 2) - pow(cy->diameter / 2, 2);
// res = det[1] * det[1] - det[0] * det[2];

t_util	init_cn_util(t_fig *cn, t_vector p1, t_vector p2)
{
	t_util	util;

	util.origin = p1;
	util.ray_dir = sub_vec(p2, p1);
	util.from_fig_center = sub_vec(p1, cn->xyz); // ec
	util.dn = dot_product(util.ray_dir, cn->normal_vec);
	util.ecn = dot_product(cn->normal_vec, util.from_fig_center);
	util.ecd = dot_product(util.ray_dir, util.from_fig_center);
	util.abc[0] = dot_product(util.ray_dir, util.ray_dir) - \
				(1 + pow(cn->diameter / 2, 2) / pow(cn->height, 2)) \
				* pow(util.dn, 2);
	util.abc[1] = util.ecd + util.dn * ((pow(cn->diameter / 2, 2) / cn->height) \
			- (1 + pow(cn->diameter / 2, 2) / pow(cn->height, 2)) * util.ecn);
	util.abc[2] = dot_product(util.from_fig_center, util.from_fig_center) \
			+ 2 * (pow(cn->diameter / 2, 2) / cn->height) * util.ecn \
			- (1 + pow(cn->diameter / 2, 2) / pow(cn->height, 2)) \
			* pow(util.ecn, 2) - pow(cn->diameter / 2, 2);
	util.det = util.abc[1] * util.abc[1] - util.abc[0] * util.abc[2];
	return (util);
}


double	parallel_to_cy_norm(t_util util, t_fig *cy, t_vector p1, t_vector p2)
{
	if (fabs(util.abc[2]) < EPSILON)
		return (get_parallel_norm_hit(cy, p1, p2));
	return (-1.0);
}

void	get_cy_solution(t_util *util, t_fig *cy)
{
	util->t[0] = (-util->abc[1] + sqrt(util->det)) / util->abc[0];
	util->t[1] = (-util->abc[1] - sqrt(util->det)) / util->abc[0];
	util->alpha = dot_product(util->origin, cy->normal_vec) \
				+ util->t[0] * util->dn \
				- dot_product(cy->xyz, cy->normal_vec);
	util->beta = util->alpha + (util->t[1] - util->t[0]) * util->dn;
}

// t[0] = (-det[1] + sqrt(res)) / det[0];
// alpha = t[0] * dn + ecn;
// beta = alpha - t[0] * dn;
// t[1] = (-det[1] - sqrt(res)) / det[0];
// beta += t[1] * dn;

void	get_cn_solution(t_util *util)
{
	util->t[0] = (-util->abc[1] + sqrt(util->det)) / util->abc[0];
	util->t[1] = (-util->abc[1] - sqrt(util->det)) / util->abc[0];
	util->alpha = util->t[0] * util->dn + util->ecn;
	util->beta = util->alpha + (util->t[1] - util->t[0]) * util->dn;
}

double	handle_cy_positive(t_util util, t_fig *cy, int *flag)
{
	if (util.t[0] < util.t[1])
	{
		// 옆
		if (util.alpha > 0 && util.alpha <= cy->height)
			return (util.t[0]);
		// 위
		else
		{
			*flag = 1;
			return (find_eqution(cy, util, util.t[0], util.t[1]));
		}
	}
	else
	{
		if (util.beta > 0 && util.beta <= cy->height) // 옆면
			return (util.t[1]);
		// 위
		else
		{
			*flag = 1;
			return (find_eqution(cy, util, util.t[1], util.t[0]));
		}
	}
}

double	handle_cn_positive(t_util util, t_fig *cn)
{
	if (util.t[0] < util.t[1])
	{
		if (util.alpha > 0 && util.alpha <= cn->height)
			return (util.t[0]);
		else
			return (util.t[1]);
	}
	else
	{
		if (util.beta > 0 && util.beta <= cn->height)
			return (util.t[1]);
		else
			return (util.t[0]);
	}
}


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
	if ((util.alpha < 0 && util.beta < 0) \
		|| (util.alpha > cn->height && util.beta > cn->height) \
		|| (util.t[0] <= 0 && util.t[1] <= 0))
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
