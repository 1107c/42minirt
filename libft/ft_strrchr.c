/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:46:09 by ksuh              #+#    #+#             */
/*   Updated: 2024/02/29 19:51:23 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	m;

	m = ft_strlen(s);
	s += m;
	if (c == 0)
		return ((char *)(s));
	while (m--)
	{
		s--;
		if (*s == c)
			return ((char *)s);
	}
	return (0);
}
