/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:08:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/11 16:22:14 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"

// static int	get_matrix(t_fig *cy, t_vector *p1, t_vector *p2, double h);

// p: plane->normal_vec->x, q: plane->normal_vec->y, r: plane->normal_vec->z
// a: point->x, b: point->y, c: point->z
// a': cam->x, b': point->y, c': point->z
// d: p*plane->x + q*plane->y+ r*plane->z

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

int	intersect_plane(t_fig *plane, t_vector *point, t_vector *cam)
{
	double	d;
	double	res;

	d = dot_product(plane->normal_vec, plane->xyz) \
		- dot_product(plane->normal_vec, cam);
	res = plane->normal_vec->x * (point->x - cam->x) + \
		plane->normal_vec->y * (point->y - cam->y) + \
		plane->normal_vec->z * (point->z - cam->z);
	if (res < 0.001 && res > -0.001)
		return (d == 0);
	d /= res;
	return (d > 0);
}

// int	intersect_sphere(t_ray *ray, t_fig *fig)
// {
// 	t_vector	*tvec;
// 	double	abc[3];
// 	double	disc;
// 	double	t[2];

// 	tvec = sub_vec(ray->origin, fig->xyz);

// 	abc[0] = dot_product(ray->direction, ray->direction);
// 	abc[1] = 2.0 * dot_product(tvec, ray->direction);
// 	abc[2] = dot_product(tvec, tvec) - (fig->diameter * fig->diameter) / 4;	
// 	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
// 	if (disc < 0)
// 		return (0);
// 	return (1);
// 	// t[0] = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
// 	// t[1] = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);

// 	// if (t[0] > 0 && t[0] < t[1])
// 	// 	return (t[0]);
// 	// if (t[1] > 0)
// 	// 	return (t[1]);
// 	// return (-1.0);
// }


// a = p1->x, b = p1->y, c = p1->z
// a'= p2.x, b'= p2.y, c'= p2.z
// a'' = sphere->x, b'' = sphere->y, c'' = sphere->z
// r = radius

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

// double intersect_sphere(t_vector *sphere_center, t_vector *ray_origin, t_vector *ray_direction, double radius)
// {
//     t_vector oc;
//     double a, b, c, discriminant;

//     // oc는 광선의 시작점에서 구의 중심을 향하는 벡터
//     oc.x = ray_origin->x - sphere_center->x;
//     oc.y = ray_origin->y - sphere_center->y;
//     oc.z = ray_origin->z - sphere_center->z;

//     // 레이-구 교차 방정식의 계수 계산
//     a = dot_product(ray_direction, ray_direction);
//     b = 2.0 * dot_product(&oc, ray_direction);
//     c = dot_product(&oc, &oc) - radius * radius;

//     // 판별식 계산
//     discriminant = b * b - 4 * a * c;

//     if (discriminant < 0)
//     {
//         // 교차점 없음
//         return -1.0;
//     }
//     else if (discriminant == 0)
//     {
//         // 한 점에서 접함
//         return -b / (2.0 * a);
//     }
//     else
//     {
//         // 두 교차점 중 가까운 것 선택
//         double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
//         double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
        
//         if (t1 > 0 && t2 > 0)
//             return (t1 < t2) ? t1 : t2;
//         else if (t1 > 0)
//             return t1;
//         else if (t2 > 0)
//             return t2;
//         else
//             return -1.0;  // 둘 다 음수면 레이의 반대 방향에 구가 있음
//     }
// }

double	intersect_sphere(t_vector *sphere, t_vector *p1, t_vector *p2, double radius)
{
	t_vector	vec1;
	t_vector	vec2;
	double		det[3];
	double		res;
	double		d;

	vec1.x = p2->x - p1->x;
	vec1.y = p2->y - p1->y;
	vec1.z = p2->z - p1->z;
	vec2.x = p1->x - sphere->x;
	vec2.y = p1->y - sphere->y;
	vec2.z = p1->z - sphere->z;
	det[0] = dot_product(&vec1, &vec1);
	det[1] = dot_product(&vec1, &vec2);
	det[2] = dot_product(&vec2, &vec2) - radius * radius;
	res = det[1] * det[1] - det[0] * det[2];
	if (res < -0.001)
		return (0);
	d = (-det[1] - sqrt(res)) / det[0];
	if (d > 0)
		return (d);
	d = (-det[1] + sqrt(res)) / det[0];
	if (d > 0)
		return (1);
	return (0);
}

// int	intersect_cylinder(t_fig *cy, t_vector *p1, t_vector *p2)
// {
// 	t_vector	vec1;
// 	t_vector	vec2;
// 	t_vector	vec3;
// 	double		dist;
// 	double		h;
// 	double		c;
// 	double		s;

// 	if (cy->height == 0)
// 		return (0);
// 	vec1 = sub_vec(p2, p1);
// 	vec2 = cross_product(&vec1, cy->normal_vec);
// 	vec3 = sub_vec(cy->xyz, p1);
// 	dist = dot_product(&vec2, &vec3) / sqrt(dot_product(&vec3, &vec3));
// 	if (dist < 0)
// 		dist = -dist;
// 	if (dist > cy->diameter / 2)
// 		return (0);
// 	if (dist == 0)
// 	{
// 		h = sqrt(dot_product(&vec3, &vec3));
// 		c = dot_product(&vec1, &vec3) / (sqrt(dot_product(&vec3, &vec3)) * sqrt(dot_product(&vec1, &vec1)));
// 		s = sqrt(1 - c*c);
// 		dist = h * s/c;
// 		if (dist < 0)
// 			dist = -dist;
// 		return (dist <= cy->diameter / 2);
// 	}
// 	// return (1);
// 	// return (0);
// 	return get_matrix(cy, p1, p2, dist);
// }

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

// t = (DE - BF) / (AD - BC)
// 0 < t <= 1 -> true
// t = 0 false
// t < 0 => h = -t * sqrt(C)
// t > 1 => h = (t - 1) * sqrt(C)
// cos(theta) = A / (sqrt(C) * sqrt(-B))
// sin(theta) = sqrt(1 - cos(theta) * cos(theta))
// tan(theta) = sin(theta) / cos(theta)
// r' = r + tan(theta) * h
// int	get_matrix(t_fig *cy, t_vector *p1, t_vector *p2, double h)
// {
// 	t_vector	vec1;
// 	t_vector	vec2;
// 	double		arr[6];
// 	double		t;
// 	double		det;

// 	vec1 = sub_vec(p2, p1);
// 	arr[0] = dot_product(cy->normal_vec, &vec1);
// 	arr[1] = -dot_product(&vec1, &vec1);
// 	arr[2] = dot_product(cy->normal_vec, cy->normal_vec);
// 	arr[3] = -arr[0];
// 	vec2 = sub_vec(p1, cy->xyz);
// 	arr[4] = dot_product(&vec2, &vec1);
// 	arr[5] = dot_product(&vec2, cy->normal_vec);
// 	det = arr[0] * arr[3] - arr[1] * arr[2];
// 	if (det > -0.001 && det < 0.001)
// 		return (1);
// 	t = (arr[3] * arr[4] - arr[1] * arr[5]) / det;
// 	if (t > 0 && t <= cy->height)
// 		return (1);
// 	if (t < 0)
// 		arr[3] = -t + cy->height;
// 	else
// 		arr[3] = t;
// 	arr[4] = arr[0] / (sqrt(arr[2]) * sqrt(-arr[1]));
// 	arr[5] = sqrt(1 - arr[4] * arr[4]);
// 	arr[5] /= arr[4];
// 	arr[3] = arr[3] * arr[5] + h;
// 	printf("t, r': %lf, %lf, %lf, %lf\n", t, arr[3], arr[5], h);
// 	return (arr[3] >= cy->diameter / 2);
// }

// 구 구조체
// {

// }
// 원기둥
// {

// }
// 땅
// {

// }
// 물체
// {
// 	타입 변수
// 	union obj
// 	{
// 		구	구변수
// 		원기둥 원기둥변수
// 		땅 땅변수
// 	};
// 	물체 next
	
// }
// n = cy->normal_vec

int	intersect_cylinder(t_fig *cy, t_vector *p1, t_vector *p2)
{
	t_vector	vec1;
	t_vector	vec2;
	t_vector	vec3;
	double		det[3];
	double		dn;
	double		res;
	double		t;
	double		alpha;
	double		beta;
	double		dist;

	vec1 = sub_vec(p2, p1); // d
	vec2 = sub_vec(p1, cy->xyz); // e - c
	vec3 = cross_product(&vec1, cy->normal_vec);
	dist = dot_product(&vec2, &vec3) / sqrt(dot_product(&vec3, &vec3));
	if (dist < 0)
		dist = -dist;
	res = dot_product(&vec1, cy->normal_vec) / dot_product(&vec1, &vec1);
	if ((res == 1 || res == -1) && dist <= cy->diameter / 2)
		return (2);
	dn = dot_product(&vec1, cy->normal_vec);
	det[0] = dot_product(&vec1, &vec1) - dn * dn;
	det[1] = dot_product(&vec1, &vec2) - dot_product(&vec2, cy->normal_vec) * dn;
	det[2] = dot_product(&vec2, &vec2) - dot_product(&vec2,	cy->normal_vec) * \
			dot_product(&vec2, cy->normal_vec) - (cy->diameter * cy->diameter) / 4;
	res = det[1] * det[1] - det[0] * det[2];
	if (res < 0)
		return (0);
	t = (-det[1] + sqrt(res)) / det[0];
	alpha = dot_product(p1, cy->normal_vec) + t * dn - dot_product(cy->xyz, cy->normal_vec);
	beta = alpha - t * dn;
	t = (-det[1] - sqrt(res)) / det[0];
	beta += t * dn;
	if ((alpha < 0 && beta < 0) || (alpha > cy->height && beta > cy->height))
		return (0);
	// if (res < 100000 && res > -100000)
		// return (1);
	if ((alpha > -0.1 && alpha < 0.1) || (alpha > cy->height - 0.1 && alpha < cy->height + 0.1))
		return (1);
	if ((beta > -0.1 && beta < 0.1) || (beta > cy->height - 0.1 && beta < cy->height + 0.1))
		return (1);
	// printf("alpha, beta, res: %lf, %lf, %lf\n", alpha, beta, res);
	// printf("norm: %lf, %lf, %lf\n", cy->normal_vec->x, cy->normal_vec->y, cy->normal_vec->z);
	return (2);
}
