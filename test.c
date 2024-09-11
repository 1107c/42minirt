/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:19:02 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/11 14:37:00 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <math.h>

static ssize_t	ft_atoss(const char *s);

ssize_t	ft_atoss(const char *s)
{
	ssize_t	res;
	ssize_t	sign;

	res = 0;
	sign = 1;
	while ((*s >= '\t' && *s <= '\r') || *s == ' ')
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s++ == '-')
			sign = -1;
	}
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		if (res > INT_MAX)
			break ;
		s++;
	}
	return (sign * res);
}

double ft_atod(char *str)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t k;
	double	front;
	double	back;

	j = 1;
	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '\0')
		return ((double)ft_atoss(str));
	str[i] = '\0';
	front = (double)ft_atoss(str);
	k = i + 1;
	while (str[++i])
		j *= 10;
	back = (double)ft_atoss(str + k) / (double)j;
	if (str[0] == '-')
		front -= back;
	else
		front += back;
	str[k - 1] = '.';
	return(roundf(front * 10) / 10);
}
int main()
{
	char a[] = "-1.1";
	printf("%f\n", ft_atod(a));
	printf("%f\n", ft_atod(a));
}