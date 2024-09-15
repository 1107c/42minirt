/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:15:46 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/08 12:15:46 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	file_check(t_rt *rt, char *av)
{
	int	fd;
	int	i;

	fd = open(av, O_RDONLY);
	i = ft_strlen(av) - 3;
	if (fd == -1 || ft_strncmp(av + i, ".rt", 3))
		return (print_err(FDERR));
	if (file_parse(rt, fd))
		return (print_err(PSERR));
	return (0);
}

int	file_parse(t_rt *rt, int fd)
{
	char	*line;
	int	i;

	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\n' && line[1] == '\0')
		{
			free(line);
			continue ;
		}
		i = rt_parse(rt, line);
		if (i == 1)
		{
			//all_free(rt);
			free(line);
			break ;
		}
	}
	close(fd);
	return (i);
}

int	rt_parse(t_rt *rt, char *line)
{
	int	i;
	char	*tmp;

	i = -1;
	tmp = line;
	while (tmp && tmp[++i])
		if (tmp[i] == '\t' || tmp[i] == '\n')
			tmp[i] = ' ';
	line = ft_strtrim(tmp, " ");
	i = name_parse(rt, line);
	free(tmp);
	if (!line)
		return (0);
	free(line);
	return (i);
}

int	name_parse(t_rt *rt, char *line)
{
	if (!ft_strncmp(line, "A", 1))
		return (set_amb(rt, line));
	else if (!ft_strncmp(line, "C", 1))
		return (set_cam(rt, line));
	else if (!ft_strncmp(line, "L", 1))
		return (set_light(rt, line));
	else if (!ft_strncmp(line, "pl", 2))
		return (set_obj(rt, line, PLANE, PLANE_G));
	else if (!ft_strncmp(line, "sp", 2))
		return (set_obj(rt, line, SPHERE, SPHERE_G));
	else if (!ft_strncmp(line, "cy", 2))
		return (set_obj(rt, line, CYLINDER, CYLINDER_G));
	return (1);
}
