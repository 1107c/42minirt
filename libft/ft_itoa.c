/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:21:22 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/29 15:26:32 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_plus_itoa(int n, size_t x, int i, int j)
{
	char	*result_arr;

	x = 1;
	while ((size_t)n >= x)
	{
		x *= 10;
		i++;
	}
	x /= 10;
	result_arr = (char *)malloc(sizeof(char) * (i + 1));
	if (result_arr == 0)
		return (0);
	while (j < i)
	{
		result_arr[j] = (n / x) + 48;
		n -= (n / x) * x;
		x /= 10;
		j++;
	}
	result_arr[j] = 0;
	return (result_arr);
}

static char	*ft_minus_itoa(size_t n, size_t x, int i, int j)
{
	char	*result_arr;

	x = 1;
	while (n >= x)
	{
		x *= 10;
		i++;
	}
	x /= 10;
	result_arr = (char *)malloc(sizeof(char) * (i + 1));
	if (result_arr == 0)
		return (0);
	result_arr[j++] = '-';
	while (j < i)
	{
		result_arr[j] = (n / x) + 48;
		n -= (n / x) * x;
		x /= 10;
		j++;
	}
	result_arr[j] = 0;
	return (result_arr);
}

char	*ft_itoa(int n)
{
	char	*result_arr;
	size_t	n2;

	if (n > 0)
	{
		result_arr = ft_plus_itoa(n, 1, 0, 0);
		return (result_arr);
	}
	else if (n == 0)
	{
		result_arr = (char *)malloc(sizeof(char) * (2));
		result_arr[0] = '0';
		result_arr[1] = 0;
		return (result_arr);
	}
	else
	{
		n2 = -1 * (size_t)n;
		result_arr = ft_minus_itoa(n2, 1, 1, 0);
		return (result_arr);
	}
}
/*
#include <stdio.h>
int main()
{
	int a;
	char *s1;
	a = -2147483648;
	s1 = ft_itoa(0);
	printf("%s\n", s1);
	free (s1);
}*/