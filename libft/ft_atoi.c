/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:41:35 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/29 13:41:19 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_white(const char **nptr)
{
	while (**nptr == 32 || (**nptr >= 9 && **nptr <= 13))
		(*nptr)++;
}

static void	minus_check(const char **nptr, int *minus)
{
	if (**nptr == '-' || **nptr == '+')
	{
		if (**nptr == '-')
			*minus *= -1;
		(*nptr)++;
	}
}

int	ft_atoi(const char *nptr)
{
	int	total;
	int	x;
	int	i;
	int	minus;

	total = 0;
	x = 1;
	i = 0;
	minus = 1;
	skip_white(&nptr);
	minus_check(&nptr, &minus);
	while (nptr[i] && (nptr[i] >= '0') && (nptr[i] <= '9'))
		i++;
	if (i == 0)
		return (0);
	while (i--)
	{
		total += x * (nptr[i] - 48);
		x *= 10;
	}
	return (minus * total);
}
/*
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char s1[] = "h";
	char s2[] = "1234567";
	char s3[] = "+--+1234567";
	char s4[] = "   +-1234567";
	char s5[] = "-1234-567";
	char s6[] = "   1234567";
	printf("%d %d\n", atoi(s1), ft_atoi(s1));
	printf("%d %d\n", atoi(s2), ft_atoi(s2));
	printf("%d %d\n", atoi(s3), ft_atoi(s3));
	printf("%d %d\n", atoi(s4), ft_atoi(s4));
	printf("%d %d\n", atoi(s5), ft_atoi(s5));
	printf("%d %d\n", atoi(s6), ft_atoi(s6));
}*/