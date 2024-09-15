/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:15:46 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/08 12:15:46 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	color_parse(t_color *color, char *arg)
{
	char	**tmp;
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	tmp = ft_split(arg, ',');
	while (tmp && tmp[++i])
		if (!ft_isulong(tmp[i]))
			ret = 1;
	if (ft_gridcount(tmp) != 3)
		ret = 1;
	else
	{
		color->r = (double) ft_coloratoi(tmp[0]) / 255;
		color->g = (double) ft_coloratoi(tmp[1]) / 255;
		color->b = (double) ft_coloratoi(tmp[2]) / 255;
	}
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	//ft_2dfree(tmp);
	return (ret);
}

int	vec_parse(char *line, t_vec *vec)
{
	char	**tmp;
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	tmp = ft_split(line, ',');
	while (tmp && tmp[++i])
		if (!is_double(tmp[i]))
			ret = 1;
	if (ft_gridcount(tmp) != 3)
		ret = 1;
	else
	{
		vec->x = (double) ft_stod(tmp[0]);
		vec->y = (double) ft_stod(tmp[1]);
		vec->z = (double) ft_stod(tmp[2]);
	}
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	//ft_2dfree(tmp);
	return (ret);
}

int	normal_parse(char *line, t_vec *vec, double min, double max)
{
	char	**tmp;
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	tmp = ft_split(line, ',');
	while (tmp && tmp[++i])
		if (!is_double(tmp[i]))
			ret = 1;
	if (ft_gridcount(tmp) != 3)
	{
		ret = 1;
		printf("ret2: %d\n", ret);
	}
	else
	{
		vec->x = (double) ft_stod(tmp[0]);
		vec->y = (double) ft_stod(tmp[1]);
		vec->z = (double) ft_stod(tmp[2]);
	}
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	//ft_2dfree(tmp);
	if (vec->x > max || vec->y > max || vec->z > max \
		|| vec->x < min || vec->y < min || vec->z < min)
		ret = 1;
	return (ret);
}

int	fov_parse(char *line, int *fov, int min, int max)
{
	int	ret;
	int	i;

	i = ft_atoi(line);
	ret = 1;
	if (i >= min && i <= max)
	{
		*fov = i;
		ret = 0;
	}
	return (ret);
}

void	obj_line_up(t_object *to, t_object **obj)
{
	t_object	*tmp;

	if (!(*obj))
		*obj = to;
	else
	{
		tmp = *obj;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = to;
	}

}
