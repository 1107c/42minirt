/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:32:01 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/28 21:45:25 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	i2;

	i = 0;
	while (s[i])
		i++;
	if (c == 0)
		return ((char *)s + i);
	i2 = i;
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (i != i2)
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
	char target = 'o';
	char target2 = 'a';
	char *found;
    char *ft_found;
	found = strchr(str, target);
    ft_found = ft_strchr(str, target);
    printf("%s\n", found);
    printf("%s\n", ft_found);
	found = strchr(str, target2);
    ft_found = ft_strchr(str, target2);
    printf("%s\n", found);
    printf("%s\n", ft_found);
	return 0;
}
*/