/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:16:51 by ksuh              #+#    #+#             */
/*   Updated: 2024/02/29 20:00:08 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char		*dest;
	size_t		m;

	m = ft_strlen(s);
	dest = (char *)malloc((m + 1) * sizeof(char));
	if (!dest)
		return (0);
	ft_strlcpy(dest, s, m + 1);
	return (dest);
}
