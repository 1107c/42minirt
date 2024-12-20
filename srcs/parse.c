/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:55:55 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/16 06:49:10 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_valid_nums(char **args);
static int	is_valid_num(char **s, int *dot, int *comma);
static void	parse_args(t_rt *rt, char **args);
static void	check_data(t_rt *rt);

// 1. 각각의 요소들은 하나 이상의 개행으로 구분되어야 함
// 2. 요소 각각의 정보들은 하나 이상의 공백으로 구분되어야 함
// 3. 순서는 상관없이
// 4. 도형을 제외한 A, C, L(영어 대문자로 구성된 요소)들은 단 한번만 나와야 합니다.

// .rt 파일을 get_next_line함수로 한 줄씩 읽으면서 유효한지 검사하는 함수
void	parse_data(t_rt *rt)
{
	char	**args;

	while (1)
	{
		rt->line = get_next_line(rt->file_fd);
		if (!rt->line)
			break ;
		if (rt->line[0] != '\n')
		{
			args = ft_split(rt->line, ft_isspace);
			if (!args)
				close_all(rt, MEM_ALLOC_ERR);
			if (!is_valid_nums(args + 1))
				close_all(rt, FORMAT_ERR);
			parse_args(rt, args);
			free_args(args);
		}
		free(rt->line);
	}
	check_data(rt);
	rt->line = NULL;
	close(rt->file_fd);
	rt->file_fd = 0;
	get_fig_idx_vec(rt);
}

// func_valid_data(arg) char값의 유효성을 검사하는 함수
// 유효하지 않은 경우
// 1. 한 숫자단위 내에 소수점이 여러개 있을 경우 => ex) 0.333.2
// 2. 소수점 뒤에 오는 문자가 숫자가 아닌 경우 => ex) 0.,
// 3. 쉼표 뒤에(+,-부호를 건너 뛴)오는 문자가 숫자가 아닌 경우 => ex) ,+,
// 4. 쉼표가 3개 이상 나오는 경우
// 5. 숫자가 아닌 값이 오는 경우

int	is_valid_nums(char **args)
{
	char	*s;
	int		dot;
	int		comma;

	while (*args)
	{
		s = *args++;
		dot = 0;
		comma = 0;
		if (*s == '+' || *s == '-')
			s++;
		if (!ft_isdigit(*s))
			return (0);
		while (*s)
		{
			if (!is_valid_num(&s, &dot, &comma))
				return (0);
			s++;
		}
		if (comma == 1)
			return (0);
	}
	return (1);
}

int	is_valid_num(char **s, int *dot, int *comma)
{
	if (**s == '.')
	{
		if (*dot || !ft_isdigit(*(*s + 1)))
			return (0);
		(*dot)++;
	}
	else if (**s == ',')
	{
		if (*comma == 2)
			return (0);
		(*comma)++;
		(*dot) = 0;
		if (*(*s + 1) == '+' || *(*s + 1) == '-')
			(*s)++;
		return (ft_isdigit(*(*s + 1)));
	}
	else if (!ft_isdigit(**s))
		return (0);
	return (1);
}

void	parse_args(t_rt *rt, char **args)
{
	if (!ft_strcmp(args[0], "A"))
		parse_amb(rt, args);
	else if (!ft_strcmp(args[0], "C"))
		parse_cam(rt, args);
	else if (!ft_strcmp(args[0], "L"))
		parse_light(rt, args);
	else if (!ft_strcmp(args[0], "pl"))
		parse_plane(rt, args, PLANE);
	else if (!ft_strcmp(args[0], "sp"))
		parse_sphere(rt, args, SPHERE);
	else if (!ft_strcmp(args[0], "cy"))
		parse_cylinder(rt, args, CYLINDER);
	else if (!ft_strcmp(args[0], "co"))
		parse_cylinder(rt, args, CONE);
	else
		free_2d_and_close_all(rt, args, INVALID_OPT);
}

void	check_data(t_rt *rt)
{
	if (rt->amblight->cnt != 1)
		close_all(rt, AMB_INPUT_ERR);
	if (rt->cam->cnt != 1)
		close_all(rt, CAM_INPUT_ERR);
	if (!rt->light)
		close_all(rt, LIGHT_INPUT_ERR);
	if (!rt->fig)
		close_all(rt, FIG_INPUT_ERR);
}
