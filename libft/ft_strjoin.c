/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:35:33 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/28 19:02:43 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	j = 0;
	s3 = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (s3 == 0)
		return (0);
	while (i < s1_len)
	{
		s3[i] = s1[i];
		i++;
	}
	while (j < s2_len)
		s3[i++] = s2[j++];
	s3[i] = 0;
	return (s3);
}
/*
#include <stdio.h>
int main()
{
	char s1[] = "hello ";
	char s2[] = "world";
	char *s3;
	s3 = ft_strjoin(s1, s2);
	printf("%s\n", s3);
}*/