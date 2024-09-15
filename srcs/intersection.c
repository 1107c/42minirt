/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:08:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/16 06:04:03 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <math.h>

static double	get_traingle_height(t_fig *cy, t_vector point);
static t_vector	get_point(t_vector p1, t_vector p2, double t);

// 두 점 P(a, b, c), P'(a', b', c')을 지나는 직선의 방정식은 다음과 같다.
// x - a / (a' - a) = y - b / (b' - b) = z - c / (c' - c)		---- 1

// 한 점 P''(a'', b'', c'')을 지나고, 법선벡터가 n(p, q, r)인 평면의 방정식:
// px + qy + rz = pa'' + qb'' + rc''							---- 2

// 1 = t로 두고 x, y, z를 매개변수 t로 치환하면 (0 < t, P(a, b, c)가 카메라의 위치이기 때문)
// x = (a' - a)t + a
// y = (b' - b)t + b
// z = (c' - c)t + c

// (x, y, z) 가 평면위에 있어야할 조건을 구해본다면
// p((a' - a)t + a) + q((b' - b)t + b) + r((c' - c)t + c) = pa'' + qb'' + rc''
// (p(a' - a) + q(b' - b) + r(c' - c))t = (pa'' + qb'' + rc'') - (pa + qb + rc)
// i) p(a' - a) + q(b' - b) + r(c' - c) = 0
// 우변 = 0이면 모든 t에 대해 식이 성립 o
// 우변 != 0이면 모든 t에 대해 식이 성립 x
// i) p(a' - a) + q(b' - b) + r(c' - c) != 0
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
	if (res == 0)
	{
		if (d == 0)
			return (0.0);
		return (-1.0);
	}
	return (d / res);
}

// 두 점 P(a, b, c), P'(a', b', c')을 지나는 직선의 방정식
// x - a / (a' - a) = y - b / (b' - b) = z - c / (c' - c)		---- 1

// 반지름의 길이가 r이고 중심이 C(a'', b'' c'')인 구의 방정식
// (x - a'')**2 + (y - b'')**2 + (z - c'')**2 = r**2

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
	if (res < 0)
		return (-1.0);
	t[0] = (-det[1] - sqrt(res)) / det[0];
	t[1] = (-det[1] + sqrt(res)) / det[0];
	if (t[0] > 0 && t[0] > t[1])
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

double	find_eqution(t_fig *cy, t_vector p1, t_vector p2, double t[2])
{
	t_vector	d;
	double		c;
	double		tanh;
	double		h;
	double		x;

	d = sub_vec(p2, p1);
	c = dot_product(d, cy->normal_vec) / sqrt(dot_product(d, d));
	if (c < 0)
		c = -c;
	tanh = sqrt(1 - c * c) / c;
	h = get_traingle_height(cy, get_point(p1, d, t[0]));
	x = (cy->diameter / tanh);
	return (t[1] * h / x + t[0] * (x - h) / x);
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
	double		hyp;
	double		height;
	double		total_dist;

	closer_area = get_closest_center(cy, point);
	t[0] = sub_vec(closer_area, point);
	hyp = sqrt(dot_product(t[0], t[0]));
	height = hyp * fabs(dot_product(t[0], cy->normal_vec));
	t[1] = sub_vec(end, point);
	total_dist = sqrt(dot_product(t[1], t[1]));
	return (height / total_dist);
}

double	intersect_cylinder(t_fig *cy, t_vector p1, t_vector p2, int *flg)
{
	t_vector	vec1;
	t_vector	vec2;
	t_vector	vec3;
	double		det[3];
	double		dn;
	double		res;
	double		t[2];
	double		_t[2];
	double		alpha;
	double		beta;
	double		dist;

	vec1 = sub_vec(p2, p1); // d
	vec2 = sub_vec(p1, cy->xyz); // e - c
	vec3 = cross_product(vec1, cy->normal_vec);
	dist = dot_product(vec2, vec3) / sqrt(dot_product(vec3, vec3));
	if (dist < 0)
		dist = -dist;
	res = dot_product(vec1, cy->normal_vec) / dot_product(vec1, vec1);
	if ((res == 1 || res == -1) && dist <= cy->diameter / 2)
		return (get_parallel_norm_hit(cy, p1, p2));
	dn = dot_product(vec1, cy->normal_vec);
	det[0] = dot_product(vec1, vec1) - dn * dn;
	det[1] = dot_product(vec1, vec2) - dot_product(vec2, cy->normal_vec) * dn;
	det[2] = dot_product(vec2, vec2) - dot_product(vec2, cy->normal_vec) * \
			dot_product(vec2, cy->normal_vec) - (cy->diameter * cy->diameter) / 4;
	res = det[1] * det[1] - det[0] * det[2];
	if (res < 0)
		return (-1.0);
	t[0] = (-det[1] + sqrt(res)) / det[0];
	alpha = dot_product(p1, cy->normal_vec) + t[0] * dn - dot_product(cy->xyz, cy->normal_vec);
	beta = alpha - t[0] * dn;
	t[1] = (-det[1] - sqrt(res)) / det[0];
	beta += t[1] * dn;
	if ((alpha < 0 && beta < 0) || (alpha > cy->height && beta > cy->height))
		return (-1.0);
	if (t[0] <= 0 && t[1] <= 0)
		return (-1.0);
	if ((t[0] > 0 && t[1] > 0))
	{
		if (t[0] < t[1])
		{
			// 옆
			if (alpha > 0 && alpha <= cy->height)
				return (t[0]);
			// 위
			else
			{
				_t[0] = t[0];
				_t[1] = t[1];
				*flg = 1;
				return (find_eqution(cy, p1, p2, _t));
			}
		}
		else
		{
			if (beta > 0 && beta <= cy->height) // 옆면
				return (t[1]);
			// 위
			else
			{
				_t[0] = t[1];
				_t[1] = t[0];
				*flg = 1;
				return (find_eqution(cy, p1, p2, _t));
			}
		}
	}
	//*flg = 1;
	return (0.0);
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
double	intersect_cone(t_fig *cy, t_vector p1, t_vector p2)
{
	t_vector	vec1;
	t_vector	vec2;
	double		dn;
	double		ecn;
	double		ecd;
	double		det[3];
	double		res;
	double		t[2];
	double		alpha;
	double		beta;

	// if (is_parallel_cone(cy, p1, p2))
	// {

	// }
	vec1 = sub_vec(p2, p1); // d
	vec2 = sub_vec(p1, cy->xyz); // e - c
	dn = dot_product(vec1, cy->normal_vec);
	ecn = dot_product(cy->normal_vec, vec2);
	ecd = dot_product(vec1, vec2);
	det[0] = dot_product(vec1, vec1) - (1 + pow(cy->diameter / 2, 2) / pow(cy->height, 2)) * pow(dn, 2);
	det[1] = ecd + (pow(cy->diameter / 2, 2) / cy->height) * dn \
			- (1 + pow(cy->diameter / 2, 2) / pow(cy->height, 2)) * ecn * dn;
	det[2] = dot_product(vec2, vec2) + 2 * (pow(cy->diameter / 2, 2) / cy->height) * ecn \
			- (1 + pow(cy->diameter / 2, 2) / pow(cy->height, 2)) * pow(ecn, 2) - pow(cy->diameter / 2, 2);
	res = det[1] * det[1] - det[0] * det[2];
	if (res < 0)
		return (-1.0);
	t[0] = (-det[1] + sqrt(res)) / det[0];
	alpha = t[0] * dn + ecn;
	beta = alpha - t[0] * dn;
	t[1] = (-det[1] - sqrt(res)) / det[0];
	beta += t[1] * dn;
	if ((alpha < 0 && beta < 0) || (alpha > cy->height && beta > cy->height))
		return (-1.0);
	if (t[0] <= 0 && t[1] <= 0)
		return (-1.0);
	if ((t[0] > 0 && t[1] > 0))
	{
		if (t[0] < t[1])
		{
			if (alpha > 0 && alpha <= cy->height)
				return (t[0]);
			else
				return (t[1]);
		}
		else
		{
			if (beta > 0 && beta <= cy->height)
				return (t[1]);
			else
				return (t[0]);
		}
	}
	return (-1.0);
}

/*
bool is_close(double a, double b) 
{
	return (fabs(a - b) < EPSILON);
}

// 점이 직선 위에 있는지 확인하는 함수
double is_point_on_line(t_vector line, t_vector point, t_vector p) {
	double t_x, t_y, t_z;

	// 방향 벡터가 0이 아닌 축에 대해서 t 값 계산
	if (fabs(line.x) > EPSILON)
		t_x = (p.x - point.x) / line.x;
	else
		t_x = NAN; // 방향 벡터가 0인 경우 t_x 계산 불가

	if (fabs(line.y) > EPSILON)
		t_y = (p.y - point.y) / line.y;
	else
		t_y = NAN; // 방향 벡터가 0인 경우 t_y 계산 불가

	if (fabs(line.z) > EPSILON)
		t_z = (p.z - point.z) / line.z;
	else
		t_z = NAN; // 방향 벡터가 0인 경우 t_z 계산 불가

	// 유효한 t 값이 있을 경우 비교 (x, y, z 중 하나라도 t 값이 있으면 됨)
	if (!isnan(t_x)) {
		if ((!isnan(t_y) && !is_close(t_x, t_y)) || \
			(!isnan(t_z) && !is_close(t_x, t_z)))
			return (-);
		return true;
	} else if (!isnan(t_y)) {
		if (!isnan(t_z) && !is_close(t_y, t_z)) 
			return (-);
		return true;
	} else if (!isnan(t_z))
		return true; // z만 유효한 경우
	return (-); // 어느 방향 벡터도 0이 아니면서 비교할 t값이 없는 경우
}
*/