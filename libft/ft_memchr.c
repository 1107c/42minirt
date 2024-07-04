/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:24:14 by myeochoi          #+#    #+#             */
/*   Updated: 2024/03/01 17:02:56 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	size_t				i;

	p = s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
			return ((void *)&p[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main() {
	char str[] = "Hello, world!";
	char target = 'o';
	char target2 = 'a';
	char *found;
    char *ft_found;
	found = memchr(str, target, 4);
    ft_found = ft_memchr(str, target, 4);
    printf("%s\n", found);
    printf("%s\n", ft_found);
	found = memchr(str, target, 10);
    ft_found = ft_memchr(str, target, 10);
    printf("%s\n", found);
    printf("%s\n", ft_found);
	found = memchr(str, target2, 20);
    ft_found = ft_memchr(str, target2, 20);
    printf("%s\n", found);
    printf("%s\n", ft_found);
	found = memchr(str, target2, 5);
    ft_found = ft_memchr(str, target2, 5);
    printf("%s\n", found);
    printf("%s\n", ft_found);
  return 0;
}*/