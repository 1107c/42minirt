/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:42:49 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/10 11:42:49 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_amb(t_rt *rt, char *line)
{
	char	**tmp;
	t_amb	amb;

	tmp = ft_split(line, ' ');
	if (rt->amb.ch == 1 || ft_gridcount(tmp) != 3)
		return (print_err(AMBERR));
	rt->amb.ch = 1;
	if (double_parse(tmp[1], &amb.ratio, 0.0, 1.0))
		return (print_err(PSERR));
	rt->amb.ratio = amb.ratio;
	if (color_parse(&amb.rgb, tmp[2]))
		return (print_err(PSERR));
	rt->amb.rgb = amb.rgb;
	//ft_2dfree(tmp);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	return (0);
}

int	set_cam(t_rt *rt, char *line)
{
	char	**tmp;
	t_cam	cam;

	tmp = ft_split(line, ' ');
	if (rt->cam.ch == 1 || ft_gridcount(tmp) != 4)
		return (print_err(CAMERR));
	rt->cam.ch = 1;
	if (vec_parse(tmp[1], &cam.coords_vec))
		return (print_err(PSERR));
	rt->cam.coords_vec = cam.coords_vec;
	if (normal_parse(tmp[2], &cam.orient_vec, -1.0, 1.0))
		return (print_err(PSERR));
	rt->cam.orient_vec = cam.orient_vec;
	if (fov_parse(tmp[3], &cam.fov, 0, 180))
		return (print_err(PSERR));
	rt->cam.fov = cam.fov;
	//ft_2dfree(tmp);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp[3]);
	free(tmp);
	return (0);
}

int	set_light(t_rt *rt, char *line)
{
	char	**tmp;
	t_light	*light;

	tmp = ft_split(line, ' ');
	if (ft_gridcount(tmp) != 4)
		return (print_err(LIGHTERR));
	light = light_memset(rt);
	if (!light)
		return (1);
	if (vec_parse(tmp[1], &light->coords_vec))
		return (print_err(PSERR));
	if (double_parse(tmp[2], &light->ratio, 0.0, 1.0))
		return (print_err(PSERR));
	if (color_parse(&light->rgb, tmp[3]))
		return (print_err(PSERR));
	//ft_2dfree(tmp);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp[3]);
	free(tmp);
	return (0);
}



int	set_obj(t_rt *rt, char *line, int type, int gc)
{
	char	**tmp;
	t_object	*obj;
	int	i;
	int	ret;

	i = 0;
	tmp = ft_split(line, ' ');
	if (ft_gridcount(tmp) != gc)
		return (print_err(OBJERR));
	obj = obj_memset(rt, type);
	if (!obj)
		return (1);
	if (type == PLANE)
		ret = set_plane(obj, tmp);
	else if (type == SPHERE)
		ret = set_sphere(obj, tmp);
	else if (type == CYLINDER)
		ret = set_cylinder(obj, tmp);
	//ft_2dfree(tmp);
	//rt->obj = obj;
	while (i < gc)
		free(tmp[i++]);
	free(tmp);
	return (ret);
}
