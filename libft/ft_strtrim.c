/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:14:22 by ksuh              #+#    #+#             */
/*   Updated: 2024/03/01 20:59:14 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	front;
	size_t	back;
	size_t	len;
	char	*dest;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	front = 0;
	back = ft_strlen(s1);
	while (back > 0 && ft_strchr(set, s1[back]))
		back--;
	if (back <= front)
		return (ft_strdup(""));
	len = back - front + 1;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	ft_strlcpy(dest, s1, len + 1);
	return (dest);
}
