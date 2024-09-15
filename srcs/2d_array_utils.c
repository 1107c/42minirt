/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_array_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:22:30 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/16 05:12:04 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// 2차원 배열의 길이를 구하는 함수
int	get_arg_len(char **args)
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
		printf("%s", *args++);
		if (*args)
			printf(" ");
	}
	printf("\n");
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
		free(args[i]);
		args[i++] = NULL;
	}
	free(args);
	args = NULL;
}
