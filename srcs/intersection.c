/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:08:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/09 15:02:49 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"

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
	if (res == 0)
		return (res == d);
	if (res < 0.001 && res > -0.001)
		return (1);
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

int	intersect_sphere(t_vector *sphere, t_vector *p1, t_vector *p2, double radius)
{
	t_vector	vec1;
	t_vector	vec2;
	double		det[3];
	double		res;

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
	if (res >= 0 || res > -0.001)
		return (1);
	return (0);
}

// int	intersect_cylinder(t_fig *cy)
// {

// }
