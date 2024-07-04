/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:31:23 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/28 20:59:10 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_p;
	unsigned char	*s2_p;
	size_t			i;

	i = 0;
	s1_p = (unsigned char *)s1;
	s2_p = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((i < n) && (s1_p[i] == s2_p[i]))
		i++;
	if (i == n)
		return (0);
	return ((int)(s1_p[i] - s2_p[i]));
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	char s1[] = "hello 1";
	char s2[] = "hello 2";
	int n;
	int n2;

	printf("%d %d\n",n = memcmp(s1, s2, 6), n2 = ft_memcmp(s1, s2, 6));
	printf("%d %d\n",n = memcmp(s1, s2, 0), n2 = ft_memcmp(s1, s2, 0));
	printf("%d %d\n",n = memcmp(s1, s2, 7), n2 = ft_memcmp(s1, s2, 7));
	printf("%d %d\n",n = memcmp(s2, s1, 7), n2 = ft_memcmp(s2, s1, 7));
}*/