/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:10:29 by ksuh              #+#    #+#             */
/*   Updated: 2024/03/01 21:15:56 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	m;
	size_t	n;

	m = ft_strlen(dest);
	if (m >= size)
		return (size + ft_strlen(src));
	n = 0;
	while (*src && m + n + 1 < size)
		dest[m + n++] = *src++;
	if (n)
		dest[m + n] = '\0';
	n += ft_strlen(src);
	return (m + n);
}
