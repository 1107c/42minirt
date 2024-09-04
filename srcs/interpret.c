/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:55:55 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 13:36:09 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	interpret_args(t_rt *rt);
static void	interpret_amb(t_rt *rt, char **args);

// ◦ Each type of element can be separated by one or more line break(s).
// ◦ Each type of information from an element can be separated by one or more space(s).
// ◦ Each type of element can be set in any order in the file.
// ◦ Elements which are defined by a capital letter can only be declared once in the scene.

// 1. 각각의 요소들은 하나 이상의 개행으로 구분되어야 함
// 2. 요소 각각의 정보들은 하나 이상의 공백으로 구분되어야 함
// 3. 순서는 상관없이
// 4. 도형을 제외한 A, C, L(영어 대문자로 구성된 요소)들은 단 한번만 나와야 합니다.

// check point
// 1. A, C, L 요소들이 무조건 한 번씩 나와야 함
// 2. 

// func_valid_data(arg) char값의 유효성을 검사하는 함수
// 유효하지 않은 경우
// 1. 한 숫자단위 내에 소수점이 여러개 있을 경우 => ex) 0.333.2
// 2. 소수점 뒤에 오는 문자가 숫자가 아닌 경우 => ex) 0.,
// 3. 쉼표 뒤에(+,-부호를 건너 뛴)오는 문자가 숫자가 아닌 경우 => ex) ,+,
// 4. 쉼표가 3개 이상 나오는 경우
// 5. 숫자가 아닌 값이 오는 경우

int	is_invalid(char **s, int *dot, int *comma)
{
	if (**s == '.')
	{
		if (*dot || !ft_isdigit(*(*s + 1)))
			return (1);
		(*dot)++;
	}
	else if (**s == ',')
	{
		if (*comma == 2)
			return (1);
		(*comma)++;
		(*dot) = 0;
		if (*(*s + 1) == '+' || *(*s + 1) == '-')
			s++;
		return (ft_isdigit(*(*s + 1)));
	}
	else if (ft_isdigit(**s))
		return (1);
	return (0);
}

int	is_valid_data(char **args)
{
	char	*s;
	int		dot;
	int		comma;

	while (*args)
	{
		s = *args++;
		dot = 0;
		comma = 0;
		if (s == '+' || s == '-')
			s++;
		if (!ft_isdigit(s))
			return (0);
		while (s)
		{
			if (is_invalid(&s, &dot, &comma))
				return (0);
			s++;
		}
		if (comma == 1)
			return (0);
	}
	return (1);
}

int	ft_iscomma(int c)
{
	return (c == ',');
}

// 2차원 배열의 길이를 구하는 함수
int		get_arg_len(char **args)
{
	int	n;

	if (!args || !*args)
		return (0);
	n = 0;
	while (args[n])
		n++;
	return (n);
}

// 2차원 배열을 프린트하는 함수
void	print_args(char **args)
{
	if (!args || !*args)
		return ;
	while (*args)
	{
		ft_putstr_fd(*args++, 1);
		if (*args)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

// 2차원 배열을 free하는 함수
void	free_args(char **args)
{
	int	i;

	if (!args || !*args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i++]);
		args[i] = NULL;
	}
	free(args);
	args = NULL;
}

// .rt 파일을 get_next_line함수로 한 줄씩 읽으면서 유효한지 검사하는 함수
void	interpret_data(t_rt *rt)
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
			if (!is_valid_data(args))
				close_all(rt, FORMAT_ERR);
			print_args(args);
			interpret_args(rt, args);
			free_args(args);
		}
		free(rt->line);
	}
	rt->line = NULL;
	close(rt->file_fd);
}

// 2차원 배열을 free하고 프로그램 종료
void	free_2d_and_close_all(t_rt *rt, char **args, char *msg)
{
	free_args(args);
	close_all(rt, msg);
}

// 요소를 구분하는 함수
void	interpret_args(t_rt *rt, char **args)
{
	if (ft_strcmp(args[0], "A"))
		interpret_amb(rt, args);
	else if (ft_strcmp(args[0], "C"))
		interpret_cam(rt, args);
	else if (ft_strcmp(args[0], "L"))
		interpret_light(rt, args);
	else if (ft_strcmp(args[0], "sp"))

	else if (ft_strcmp(args[0], "pl"))

	else if (ft_strcmp(args[0], "cy"))
		interpret_amb(rt, args);
	else
		free_2d_and_close_all(rt, args, INVALID_OPT);
}

// int 자료형이 주어진 범위에 있는지 검사
int	is_int_range(int n, int range_min, int range_max)
{
	return (n >= range_min && n <= range_max);
}

// double 자료형이 주어진 범위에 있는지 검사
int	is_double_range(double d, double range_min, double range_max)
{
	return (d >= range_min && d <= range_max);
}

// 한 개의 int 자료형 유효성 검사
int	is_valid_single_int_value(t_rt *rt, char *arg, int range_min, int range_max)
{
	int	n;

	if (ft_strchr(arg, ','))
	{
		rt->error = FORMAT_ERR;
		return (0);
	}
	n = ft_atoi(arg, range_min, range_max);
	if (!is_int_range(n, range_min, range_max))
	{
		rt->error = RANGE_ERR;
		return (0);
	}
	return (1);
}

// 한 개의 double 자료형 유효성 검사
int	is_valid_single_double_value(t_rt *rt, char *arg, double range_min, double range_max)
{
	double	d;

	if (ft_strchr(arg, ','))
	{
		rt->error = FORMAT_ERR;
		return (0);
	}
	d = ft_atod(arg);
	if (!is_int_range(d, range_min, range_max))
	{
		rt->error = RANGE_ERR;
		return (0);
	}
	return (1);
}

// vector의 double 자료형(3개) 유효성 검사
int	is_valid_multi_double_value(t_vector *vec, char *arg, double range_min, double range_max)
{
	char	**tmp;

	tmp = ft_split(arg, ft_iscomma);
	if (!tmp)
	{
		vec->error = MEM_ALLOC_ERR;
		return (0);
	}
	if (get_arg_len(tmp) != 3)
	{
		vec->error = FORMAT_ERR;
		return (free_args(tmp), 0);
	}
	vec->x = ft_atod(tmp[0]);
	vec->y = ft_atod(tmp[1]);
	vec->z = ft_atod(tmp[2]);
	if (!is_double_range(vec->x, range_min, range_max)
	|| !is_double_range(vec->y, range_min, range_max)
	|| !is_double_range(vec->z, range_min, range_max))
	{
		vec->error = RANGE_ERR;
		return (free_args(tmp), 0);
	}
	return (free_args(tmp), 1);
}

// ∗ identifier: A
// ∗ ambient lighting ratio in range [0.0,1.0]: 0.2
// ∗ R,G,B colors in range [0-255]: 255, 255, 255

void	interpret_amb(t_rt *rt, char **args)
{
	if (rt->amblight->ch)
		free_2d_and_close_all(rt, args, AMB_DUP_ERR);
	if (get_arg_len(args) != 3)
		free_2d_and_close_all(rt, args, AMB_LEN_ERR);
	if (!is_valid_single_double_value(rt, args[1], 0.0, 1.0))
		free_2d_and_close_all(rt, args, rt->error);
	rt->amblight->light_ratio = ft_atod(args[1]);
	if (!is_valid_multi_double_value(rt->amblight->rgb, args[2], 0, 255))
		free_2d_and_close_all(rt, args, rt->amblight->rgb->error);
	rt->amblight->ch = 1;
}

// ∗ identifier: C
// ∗ x,y,z coordinates of the view point: -50.0,0,20
// ∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
// ∗ FOV : Horizontal field of view in degrees in range [0,180]: 70

void	interpret_cam(t_rt *rt, char **args)
{
	if (rt->cam->ch)
		free_2d_and_close_all(rt, args, CAM_DUP_ERR);
	if (get_arg_len(args) != 4)
		free_2d_and_close_all(rt, args, CAM_LEN_ERR);
	if (!is_valid_multi_double_value(rt->cam->xyz, args[0], INT_MIN, INT_MAX))
		free_2d_and_close_all(rt, args, rt->cam->xyz->error);
	if (!is_valid_multi_double_value(rt->cam->orient_vec, args[1], -1, 1))
		free_2d_and_close_all(rt, args, rt->cam->orient_vec->error);
	if (!is_valid_single_int_value(rt, args[2], 0, 180))
		free_2d_and_close_all(rt, args, rt->error);
	rt->cam->fov = ft_atod(args[2]);
	rt->cam->ch = 1;
}

// ∗ identifier: L
// ∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
// ∗ the light brightness ratio in range [0.0,1.0]: 0.6
// ∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255

void	interpret_light(t_rt *rt, char **args)
{
	if (rt->cam->ch)
		free_2d_and_close_all(rt, args, LIGHT_DUP_ERR);
	if (get_arg_len(args) != 4)
		free_2d_and_close_all(rt, args, LIGHT_LEN_ERR);
	if (!is_valid_multi_double_value(rt->light->xyz, args[0], INT_MIN, INT_MAX))
		free_2d_and_close_all(rt, args, rt->light->xyz->error);
	if (!is_valid_single_double_value(rt, args[1], 0, 1))
		free_2d_and_close_all(rt, args, rt->error);
	rt->light->brightness = ft_atod(args[1]);
	if (!is_valid_multi_double_value(rt->light->rgb, args[2], 0, 255))
		free_2d_and_close_all(rt, args, rt->light->rgb->error);
	rt->cam->ch = 1;
}
