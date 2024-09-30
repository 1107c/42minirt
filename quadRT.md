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
