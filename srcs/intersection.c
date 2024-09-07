/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 13:08:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/07 13:08:46 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"

int	intersect_plane(t_vector *plane, t_vector line)
{
	double	res;

	res = plane->x * line.x + plane->y * line.y + plane->z * line.z;
	// printf("res: %lf\n", res);
	return (res > 0.001);
}

int	intersect_sphere(t_ray *ray, t_fig *fig)
{
	t_vector	*tvec;
	double	abc[3];
	double	disc;
	double	t[2];

	tvec = sub_vec(ray->origin, fig->xyz);

	abc[0] = dot_product(ray->direction, ray->direction);
	abc[1] = 2.0 * dot_product(tvec, ray->direction);
	abc[2] = dot_product(tvec, tvec) - (fig->diameter * fig->diameter) / 4;	
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (0);
	return (1);
	// t[0] = (-abc[1] - sqrt(disc)) / (2.0 * abc[0]);
	// t[1] = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);

	// if (t[0] > 0 && t[0] < t[1])
	// 	return (t[0]);
	// if (t[1] > 0)
	// 	return (t[1]);
	// return (-1.0);
}

// int	intersect_sphere(t_vector *sphere, t_vector p1, t_vector p2, double radius)
// {
// 	double	res;
// 	double	first;
// 	double	second;
// 	double	third;

// 	//a = p1.x, b = p1.y, c = p1.z
// 	//a'= p2.x, b'= p2.y, c'= p2.z
// 	//p = sphere->x, q = sphere->y, r = sphere->z
// 	//s = radius
// 	// printf("sphere xyz: %lf, %lf, %lf, %lf\n", sphere->x, sphere->y, sphere->z, radius);
// 	// printf("p1 xyz: %lf, %lf, %lf\n", p1.x, p1.y, p1.z);
// 	// printf("p2 xyz: %lf, %lf, %lf\n", p2.x, p2.y, p2.z);
// 	first = (p2.x-p1.x) * (p2.x-p1.x) + (p2.y-p1.y) * (p2.y-p1.y) + (p2.z-p1.z) * (p2.z-p1.z);
// 	second = (p2.x-p1.x) * (p1.x-sphere->x) + (p2.y-p1.y) * (p1.y-sphere->y) + (p2.z-p1.z) * (p1.z-sphere->z);
// 	second *= second;
// 	third = (p1.x - sphere->x) * (p1.x - sphere->x) + (p1.y - sphere->y) * (p1.y - sphere->y) + (p1.z - sphere->z) * (p1.z - sphere->z) - radius * radius;

// 	// D/4 >= 0 second - first*third >= 0
// 	res = second - first * third;
// 	// printf("res: %lf\n", res);
// 	if (res >= 0 || res > -0.001)
// 		return (1);
// 	return (0);
// }