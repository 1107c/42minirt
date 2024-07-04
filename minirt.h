/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:25:49 by ksuh              #+#    #+#             */
/*   Updated: 2024/07/04 11:13:17 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT
# define MINI_RT

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_amb_light
{
	float	light_ratio;
	int		r;
	int		g;
	int		b;
}	t_amb_light;

typedef struct s_cam
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	int		fov;
}	t_cam;

typedef struct s_light
{
	float	x;
	float	y;
	float	z;
	float	brightness;
	int		r;
	int		g;
	int		b;	
}	t_light;

typedef struct s_sphere
{
	float	x;
	float	y;
	float	z;
	int		r;
	int		g;
	int		b;	
}	t_sphere;

typedef struct s_plane
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	int		r;
	int		g;
	int		b;	
}	t_plane;

typedef struct s_cylinder
{
	float	x;
	float	y;
	float	z;
	float	vx;
	float	vy;
	float	vz;
	float	diameter;
	float	height;
	int		r;
	int		g;
	int		b;	
}	t_cylinder;

#endif