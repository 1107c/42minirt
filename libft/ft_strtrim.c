/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:10:03 by myeochoi          #+#    #+#             */
/*   Updated: 2024/03/01 13:28:14 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_front_len(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (s1[i])
	{
		j = 0;
		flag = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
				flag = 1;
			j++;
		}
		if (flag == 0)
			break ;
		i++;
	}
	return (i);
}

static int	ft_back_len(char const *s1, char const *set)
{
	int	tot_len;
	int	i;
	int	flag;

	tot_len = ft_strlen(s1) - 1;
	while (tot_len > 0)
	{
		i = 0;
		flag = 0;
		while (set[i])
		{
			if (set[i] == s1[tot_len])
				flag = 1;
			i++;
		}
		if (flag == 0)
			break ;
		tot_len--;
	}
	return (tot_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		front_len;
	int		back_len;
	int		i;
	char	*return_arr;

	front_len = ft_front_len(s1, set);
	back_len = ft_back_len(s1, set);
	i = 0;
	if (back_len <= front_len)
	{
		return_arr = (char *)malloc(sizeof(char) * (1));
		if (return_arr == 0)
			return (0);
		return_arr[0] = 0;
	}
	else
		return_arr = (char *)malloc(sizeof(char) * (back_len - front_len + 2));
	if (return_arr == 0)
		return (0);
	while (front_len <= back_len)
		return_arr[i++] = s1[front_len++];
	return_arr[i] = 0;
	return (return_arr);
}
/*
#include <stdio.h>
int main()
{
	char s1[] = "          ";
	// char s2[] = "g ag good goa go";
	char s3[] = " ";
	// char s4[] = "a";
	char *s5;
	// char *s6;
	s5 = ft_strtrim(s1,s3);
	// s6 = ft_strtrim(s2,s3); 
	printf("%s\n", s5);
	// s5 = ft_strtrim(s1,s4);
	// s6 = ft_strtrim(s2,s4); 
	// printf("%s/%s\n", s5, s6);
	free (s5);
	// free (s6);
}*/