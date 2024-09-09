/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:21:05 by ksuh              #+#    #+#             */
/*   Updated: 2024/02/26 19:45:25 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	n;
	size_t	startidx;

	if (*little == '\0')
		return ((char *) big);
	n = ft_strlen(little);
	startidx = 0;
	while (big[startidx] && startidx + n <= len)
	{
		if (!ft_strncmp(big + startidx, little, n))
			return ((char *)(big + startidx));
		startidx++;
	}
	return (0);
}
