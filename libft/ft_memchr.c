/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:02:25 by ksuh              #+#    #+#             */
/*   Updated: 2024/02/28 20:22:09 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (n--)
	{
		if (*(unsigned char *)s == uc)
			return ((void *)(s));
		s++;
	}
	return (0);
}
