/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:15:11 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/28 20:27:37 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;
	int		leng;

	leng = 0;
	while (s[leng])
		leng++;
	s2 = (char *)malloc(sizeof(char) * (leng + 1));
	if (s2 == 0)
		return (0);
	leng = 0;
	while (s[leng])
	{
		s2[leng] = s[leng];
		leng++;
	}
	s2[leng] = 0;
	return (s2);
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
	char s1[] = "hello world";
	char *s2;
	char *s3;
	s2 = strdup(s1);
	s3 = ft_strdup(s1);
	printf("%s\n", s2);
	printf("%s\n", s3);
	free (s2);
	free (s3);
}*/