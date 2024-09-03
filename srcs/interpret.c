/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:55:55 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/03 17:31:00 by ksuh             ###   ########.fr       */
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
	return (c == ',')
}

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
			// 할당 실패시 메모리 해제 후 종료
			if (!args)
				close_all(rt, MEM_ERR);
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

	else
	{
		free_args(args);
		close_all(rt, INVALID_OPT);
	}
}

// ∗ identifier: A
// ∗ ambient lighting ratio in range [0.0,1.0]: 0.2
// ∗ R,G,B colors in range [0-255]: 255, 255, 255

void	interpret_amb(t_rt *rt, char **args)
{
	if (rt->amblight->ch)
	{
		free_args(args);
		close_all(rt, AMB_DUP_ERR);
	}
	if (get_arg_len(args) != 3)
	{
		free_args(args);
		close_all(rt, AMB_LEN_ERR);
	}
	if (ft_strchr(args[1], ','))
	{
		free(args);
		close_all(rt, AMB_RATIO_FORMAT_ERR);
	}
	rt->amblight->light_ratio = ft_atol();
	ft_split(args[2], ft_iscomma);
	rt->amblight->ch = 1;
}

void	interpret_cam(t_rt *rt, char **args)
{
	if (rt->cam->ch)
	{
		free_args(args);
		close_all(rt, CAM_DUP_ERR);
	}
	if (get_arg_len(args) != 4)
	{
		free_args(args);
		close_all(rt, CAM_LEN_ERR);
	}
	
	
	rt->cam->ch = 1;
}

void	interpret_light(t_rt *rt, char **args)
{
	if (rt->cam->ch)
	{
		free_args(args);
		close_all(rt, LIGHT_DUP_ERR);
	}
	if (get_arg_len(args) != 4)
	{
		free_args(args);
		close_all(rt, LIGHT_LEN_ERR);
	}
	rt->cam->ch = 1;
}
