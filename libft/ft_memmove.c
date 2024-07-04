/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:29:55 by myeochoi          #+#    #+#             */
/*   Updated: 2024/03/01 19:24:42 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	unsigned char	*dest_p;
	unsigned char	*src_p;
	size_t			i;

	if (dest == 0 && src == 0)
		return (0);
	dest_p = dest;
	src_p = src;
	if (src < dest)
	{
		i = n;
		while (i--)
			dest_p[i] = src_p[i];
		return ((void *)dest_p);
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dest_p[i] = src_p[i];
			i++;
		}
		return ((void *)dest_p);
	}
}
/*
#include <stdio.h>
#include <string.h>
int main() {
  char str1[] = "Sample string";
  char str2[] = "asdasdasdasda";
  char str3[40];

  memmove(str2, str1, 0);
  memmove(str3, "copy successful", 14);
  printf("str1: %s\nstr2: %s\nstr3: %s\n", str1, str2, str3);
  ft_memmove(str2, str1, 0);
  ft_memmove(str3, "copy successful", 14);
  printf("str1: %s\nstr2: %s\nstr3: %s\n", str1, str2, str3);
  return 0;
}*/