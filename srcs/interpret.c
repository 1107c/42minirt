/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:55:55 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/03 15:21:45 by ksuh             ###   ########.fr       */
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

	else if (ft_strcmp(args[0], "L"))

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
}
