/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:51:11 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/28 21:44:56 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (c == 0)
		return ((char *)s + i);
	i -= 1;
	while (i >= 0 && s[i] != c)
		i--;
	if (i > -1)
		return ((char *)(&s[i]));
	else
		return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str[] = "Hello, world!";
	// char target = 'o';
	char target2 = 'a';
	char *found;
    char *ft_found;
	found = strrchr(str, 0);
    ft_found = ft_strrchr(str, 0);
    printf("%s\n", found);
    printf("%s\n", ft_found);
	found = strrchr(str, target2);
    ft_found = ft_strrchr(str, target2);
    printf("%s\n", found);
    printf("%s\n", ft_found);
	return 0;
}*/