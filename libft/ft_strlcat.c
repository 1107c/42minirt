/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:21:48 by myeochoi          #+#    #+#             */
/*   Updated: 2024/03/02 10:37:31 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (!src)
		return (s_len + d_len);
	i = 0;
	while (src[i] && d_len + i + 1 < size)
	{
		dst[d_len + i] = src[i];
		i++;
	}
	if (i != 0)
		dst[d_len + i] = 0;
	if (d_len < size)
		return (s_len + d_len);
	else
		return (s_len + size);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	dst[] = "12345"; 
	char	src[] = "abcdefghijklmnop";
	printf("%zu\n", ft_strlcat(dst, src, 10));
	printf("%s\n", dst);
	char	dst1[] = "12345";
	char	src1[] = "abcdefghijklmnop";
	printf("%zu\n", ft_strlcat(dst1, src1, 3));
	printf("%s\n", dst1);
}
*/