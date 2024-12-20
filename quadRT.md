# PARSE
### handling error
***
1. `A`, `C`, `L` 이 포함되지 않은 경우 혹은 중복 되는 경우
   - `A` = 주변조명
   - `C` = 카메라
   - `L` = 빛
     
2. `figure`가 들어오지 않은 경우
   - 평면 = 0
   - 구 = 1
   - 원통 = 2
   - 2도 물체 : 원뿔 등
     
3. 수의 범위가 `INT_RANGE`를 벗어 난 경우
   
4. 영문자, 특수문자 포함
   
5. "`x`, `y`, `z`", "`r`, `g`, `b`" 값이 모두 들어오지 않은 경우
   - 모든 요소에 하나의 값
     
6. 각 요소들의 인자 갯수 불일치

# INTERSECTION
### plane
두 점 P(a, b, c), P'(a', b', c')을 지나는 직선의 방정식은 다음과 같다.
(x - a) / (a' - a) = (y - b) / (b' - b) = (z - c) / (c' - c)		---- *1

한 점 P''(a'', b'', c'')을 지나고, 법선벡터가 n(p, q, r)인 평면의 방정식:
px + qy + rz = pa'' + qb'' + rc''								---- *2

*1 = t로 두고 x, y, z를 매개변수 t로 치환하면 (0 < t, P(a, b, c)가 카메라의 위치이기 때문)
x = (a' - a)t + a
y = (b' - b)t + b
z = (c' - c)t + c

직선상의 점 P''(x, y, z) 가 평면위에 있어야할 조건을 구해본다면
p((a' - a)t + a) + q((b' - b)t + b) + r((c' - c)t + c) = pa'' + qb'' + rc''
(p(a' - a) + q(b' - b) + r(c' - c))t = (pa'' + qb'' + rc'') - (pa + qb + rc)
i) p(a' - a) + q(b' - b) + r(c' - c) = 0
우변 = 0이면 모든 t에 대해 식이 성립 o
우변 != 0이면 모든 t에 대해 식이 성립 x
ii) p(a' - a) + q(b' - b) + r(c' - c) != 0
((pa'' + qb'' + rc'') - (pa + qb + rc)) / p(a' - a) + q(b' - b) + r(c' - c) > 0이면
카메라 시야에서 평면과 교점이 발생

### sphere
두 점 P(a, b, c), P'(a', b', c')을 지나는 직선의 방정식
(x - a) / (a' - a) = (y - b) / (b' - b) = (z - c) / (c' - c)		---- *1

반지름의 길이가 r이고 중심이 C(a'', b'' c'')인 구의 방정식
(x - a'')**2 + (y - b'')**2 + (z - c'')**2 = r**2					---- *2

위와 마찬가지로 직선상의 점 P''(x, y, z)를 *1=t로 치환한 값을 *2에 대입하면
(t(a' - a) + (a - a''))**2 +
(t(b' - b) + (b - b''))**2 +
(t(c' - c) + (c - c''))**2 - r**2 = 0
t*t의 계수(X): (a' - a)**2 + (b' - b)**2 + (c' - c)**2
t의 계수(Y): 2((a' - a)(a - a'') + (b' - b)(b - b'') + (c' - c)(c - c''))
상수항의 계수(Z): (a - a'')**2 + (b - b'')**2 + (c - c'')**2 - r**2
t의 관한 이차방정식의 해가 존재할 조건은
D/4 >= 0 => Y**2 - XZ >= 0

# CAM
카메라 시점의 기저벡터를 구하는 과정
카메라의 orient_vec의 yz, xz로의 정사영과 z축이 이루는 각 theta, pi를 구한다.
카메라의 orient_vec가 z축 위에 있다고 가정했을 때,
해당 벡터를 y축으로 theta만큼, x축으로 pi만큼 회전한 것을 의미한다.
축의 회전에 따라 x축, y축도 같이 회전되어 바뀐 벡터를 구해주면
이것들이 곧 새로운 시점의 기저벡터들이 된다.

<CODE v1>
t_vector	proj_vector_yzx;
t_vector	z_unit_vector;
double		theta;

proj_vector_yzx = (t_vector) {0, cam->orient_vec.y, cam->orient_vec.z, 0};
z_unit_vector = (t_vector) {0, 0, 1, 0};
theta = dot_product(proj_vector_yzx, z_unit_vector) /
		sqrt(dot_product(proj_vector_yzx, proj_vector_yzx));
cam->up_vec = (t_vector) {0, theta, -sqrt(1 - theta * theta), 0};
proj_vector_yzx.x = cam->orient_vec.x;
proj_vector_yzx.y = 0;
theta = dot_product(proj_vector_yzx, z_unit_vector) /
		sqrt(dot_product(proj_vector_yzx, proj_vector_yzx));
cam->right_vec = (t_vector) {theta, 0, -sqrt(1 - theta * theta), 0};

# CONE
	// if (xs->t[0] > 0)
	// {
	// 	if (xs->alpha <= xs->h && xs->alpha >= 0)
	// 		return (xs->t[0]);
	// 	if (xs->beta >= 0 && xs->beta <= xs->h)
	// 		return (xs->t[1]);
	// 	return (-1.0);
	// }
	// else
	// {
	// 	double	d;
	// 	double	e;
	// 	double	f;

	// 	d = dot_product(xs->ray_dir, sub_vec(cn->xyz, xs->from));
	// 	e = dot_product(xs->ray_dir, sub_vec(add_vec(cn->xyz, \
	// 		mul_vec(cn->normal_vec, 2 * cn->height)), xs->from));
	// 	f = xs->dn / sqrt(dot_product(xs->ray_dir, xs->ray_dir));
	// 	if (xs->t[1] > 0)
	// 	{
	// 		if (xs->beta <= xs->h && xs->beta >= 0)
	// 			return (xs->t[1]);
	// 		if (xs->alpha > 0 && xs->beta < 0 \
	// 			&& fabs(f) <= xs->c && d >= 0 && e < 0)
	// 			return (get_cn_center_hit(cn, xs, cn->xyz));
	// 		if (xs->alpha < xs->h && xs->beta > xs->h \
	// 			&& fabs(f) <= xs->c && e >= 0 && d < 0)
	// 			return (get_cn_center_hit(cn, xs, add_vec(cn->xyz, \
	// 				mul_vec(cn->normal_vec, 2 * cn->height))));
	// 	}
	// 	else
	// 	{
	// 		if (fabs(f) >= xs->c && d >= 0 && e < 0)
	// 			return (get_cn_center_hit(cn, xs, cn->xyz));
	// 		if (fabs(f) >= xs->c && e >= 0 && d < 0)
	// 			return (get_cn_center_hit(cn, xs, add_vec(cn->xyz, \
	// 				mul_vec(cn->normal_vec, 2 * cn->height))));
	// 	}
	// }
	// return (-1.0);

/*
t_xs		init_cn_util(t_fig *cn, t_vector p1, t_vector p2)
{
	t_xs	util;
	double	radius;
	double	height_ratio;

	 util.origin = p1;
	util.ray_dir = sub_vec(p2, p1);
	 d = sub_vec(util.ray_dir, cn->normal_vec);
	 radius = cn->diameter / 2;
	 apex = add_vec(cn->xyz, mul_vec(cn->normal_vec, cn->height));
	 h = cn->height;
	 util.abc[0] = d.x * d.x + d.y * d.y - (radius * radius) / (h * h) * d.z * d.z;
	 util.abc[1] = d.x * (util.origin.x - apex.x) + d.y * (util.origin.y - apex.y) -
	 			(radius * radius) / (h * h) * d.z * (util.origin.z - apex.z);
	 util.abc[2] = (util.origin.x - apex.x) * (util.origin.x - apex.x) +
				(util.origin.y - apex.y) * (util.origin.y - apex.y) -
				(radius * radius) / (h * h) * (util.origin.z - apex.z) * (util.origin.z - apex.z);
	util.from_fig_center = sub_vec(p1, cn->xyz);
	util.dn = dot_product(util.ray_dir, cn->normal_vec);
	util.ecn = dot_product(cn->normal_vec, util.from_fig_center);
	util.ecd = dot_product(util.ray_dir, util.from_fig_center);
	radius = cn->diameter / 2;
	height_ratio = pow(radius / cn->height, 2);
	util.abc[0] = dot_product(util.ray_dir, util.ray_dir) - \
				(1 + height_ratio) \
				* pow(util.dn, 2);
	util.abc[1] = util.ecd - util.ecn * util.dn * (1 + height_ratio) \
				+ height_ratio * cn->height * util.dn;
	util.abc[2] = dot_product(util.from_fig_center, util.from_fig_center) \
			+ 2 * (pow(radius, 2) / cn->height) * util.ecn \
			- (1 + height_ratio) \
			* pow(util.ecn, 2) - pow(radius, 2);
	util.c = cn->height / sqrt(pow(radius, 2) + pow(cn->height, 2));
	util.h = cn->height * 2;
	 util.abc[0] = dot_product(util.ray_dir, util.ray_dir) - 2 * pow(util.ray_dir.y, 2);
	 util.abc[1] = util.ray_dir.x * util.origin.x - util.ray_dir.y * util.origin.y \
				+ util.ray_dir.z * util.origin.z;
	 util.abc[2] = dot_product(util.origin, util.origin) - 2 * pow(util.origin.y, 2);
	util.det = util.abc[1] * util.abc[1] - util.abc[0] * util.abc[2];
	return (util);
	}*/

	if (keycode == 112)
	{
		printf("coords: %lf,%lf,%lf\n", rt->cam->coords.x, rt->cam->coords.y, rt->cam->coords.z);
		printf("orient: %lf,%lf,%lf\n", rt->cam->orient_vec.x, rt->cam->orient_vec.y, rt->cam->orient_vec.z);
	}

		// return (EPSILON);
	// if (is_in_cylinder(cy, xs))
	// {
	// 	xs->flag = 3;
	// 	return (get_cy_up_hit(cy, xs));
	// }
	// // return (EPSILON);
	// if ((xs->beta < 0 && xs->ecd <= 0) \
	// 	|| (xs->beta > cy->height && xs->ecd >= 0))
	// 	{
	// 		printf("%lf %lf\n", xs->beta, xs->ecd);
	// 	return (-1.0);
	// 	}
	// // return (EPSILON);
	// if (xs->alpha < 0)
	// 	xs->flag = 2;
	// else
	// 	xs->flag = 1;
	// return (get_cy_up_hit(cy, xs));