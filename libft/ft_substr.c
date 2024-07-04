/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:34:33 by myeochoi          #+#    #+#             */
/*   Updated: 2024/03/01 17:08:03 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s))
	{
		s1 = malloc(1);
		s1[0] = 0;
		return (s1);
	}
	s1 = (char *)malloc(sizeof(char) * len + 1);
	if (s1 == 0)
		return (0);
	while (i < len)
		s1[i++] = s[start++];
	s1[i] = 0;
	return (s1);
}
/*
#include <stdio.h>
int main()
{
	char s1[] = "abcde";
	char *s2;
	char *s3;
	char *s4;

	s2 = ft_substr(s1, 0, 2);
	printf("%s\n", s2);
	free (s2);
	s3 = ft_substr(s1, 1, 1);
	printf("%s\n", s3);
	free (s3);
	s4 = ft_substr(s1, 0, 10);
	printf("%s\n", s4);
	free (s4);
}*/