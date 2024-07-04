/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:06:08 by myeochoi          #+#    #+#             */
/*   Updated: 2024/03/01 20:23:37 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_point
{
	size_t	i;
	size_t	j;
}	t_point;

static int	ft_strpoint(const char *big, const char *little, \
t_point *point, size_t len)
{
	int	flag;

	flag = 0;
	while ((*point).i + ft_strlen(little) <= len && big[(*point).i])
	{
		(*point).j = 0;
		if (big[(*point).i] != little[(*point).j])
			(*point).i++;
		else
		{
			while (big[(*point).i] == little[(*point).j] && little[(*point).j])
			{
				(*point).i++;
				(*point).j++;
				if (ft_strlen(little) == (*point).j)
				{
					flag = 1;
					break ;
				}
			}
		}
		if (flag == 1)
			break ;
	}
	return (flag);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	t_point	point;
	size_t	little_length;

	point.i = 0;
	point.j = 0;
	little_length = ft_strlen(little);
	if (little_length == 0)
		return ((char *)(big));
	else
	{
		if (ft_strpoint(big, little, &point, len) == 0)
			return (0);
		else
			return ((char *)(&big[point.i - point.j]));
	}
}
/*
#include<stdio.h>
#include<string.h>
int main()
{
	char big[] = "see FF your FF return FF now FF";
	char little[] = "FF";
	char little1[] = "a";
	char little2[] = "yo";
	char little3[] = "op";
	char little4[] = "os";
	printf("%s\n", ft_strnstr(big,little, strlen(big)));
	printf("%s\n", ft_strnstr(big,little,0)); 
	printf("%s\n", ft_strnstr(big,little1,14)); 
	printf("%s\n", ft_strnstr(big,little1,5)); 
	printf("%s\n", ft_strnstr(big,little2,20));
	printf("%s\n", ft_strnstr(big,little3,20));
	printf("%s\n", ft_strnstr(big,little4,20));
	return (0);
}*/