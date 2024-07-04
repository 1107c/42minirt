/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:07:32 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/29 13:20:57 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}
/*
#include <stdio.h>
int main(void)
{
    char	s1[4] = "hel";
    char	s2[6] = "world";
	size_t ret;

    ret = ft_strlcpy(s1, s2, 0);
    printf("%s %zu\n", s1, ret);
	ret = ft_strlcpy(s1, s2, 3);
    printf("%s %zu\n", s1, ret);
}*/