/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:12:48 by myeochoi          #+#    #+#             */
/*   Updated: 2024/03/01 19:24:42 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void		*dest_p;

	if (dest == 0 && src == 0)
		return (0);
	dest_p = dest;
	while (n--)
		*((unsigned char *)dest++) = *((unsigned char *)src++);
	return (dest_p);
}
/*
#include <stdio.h>
#include <string.h>
int main() {
  char str1[] = "Sample string";
  char str2[] = "asdasdasdasda";
  char str3[40];

  memcpy(str2, str1, 12);
  memcpy(str3, "copy successful", 14);
  printf("str1: %s\nstr2: %s\nstr3: %s\n", str1, str2, str3);
  ft_memcpy(str2, str1, 12);
  ft_memcpy(str3, "copy successful", 14);
  printf("str1: %s\nstr2: %s\nstr3: %s\n", str1, str2, str3);
  return 0;
}*/
