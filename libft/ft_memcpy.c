/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:21:42 by ksuh              #+#    #+#             */
/*   Updated: 2024/03/01 20:52:09 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_overlap(char *dest, const char *src, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*destcpy;
	const char	*srccpy;

	destcpy = (char *)dest;
	srccpy = (const char *)src;
	if (ft_overlap(destcpy, srccpy, n))
		return (ft_memmove(dest, src, n));
	while (n--)
		*destcpy++ = *srccpy++;
	return (dest);
}

int	ft_overlap(char *dest, const char *src, size_t n)
{
	size_t	m;

	m = 0;
	while (m < n)
	{
		if (dest + m == src || src + m == dest)
			return (1);
		m++;
	}
	return (0);
}
