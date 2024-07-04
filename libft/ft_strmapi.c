/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:54:40 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/28 16:47:31 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result_arr;
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	result_arr = (char *)malloc(sizeof(char) * (i + 1));
	if (result_arr == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		result_arr[i] = f(i, s[i]);
		i++;
	}
	result_arr[i] = 0;
	return (result_arr);
}
/*
#include<stdio.h>
char plus_one(unsigned int i, char c)
{
	return (c + i - i);
}
int main()
{
	char s1[] ="hello world"; 
	char *s2;

	s2 = ft_strmapi(s1, plus_one);
	printf("%s\n", s2);
	free (s2);
}*/