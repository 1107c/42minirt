/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:59:04 by ksuh              #+#    #+#             */
/*   Updated: 2024/02/29 19:42:06 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	m;

	m = 0;
	while (*src && m + 1 < size)
		dest[m++] = *src++;
	if (size)
		dest[m] = '\0';
	return (m + ft_strlen(src));
}
