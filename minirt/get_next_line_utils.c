/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:39:45 by yeojukim          #+#    #+#             */
/*   Updated: 2024/03/20 14:39:47 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l;
	char	*ret;

	l = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (l + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, l + 1);
	ft_strlcat(ret, s2, l + 1);
	return (ret);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (ft_strlen(src));
	while (*src && i + 1 < size)
	{
		*dst++ = *src++;
		i++;
	}
	*dst = '\0';
	while (*src++)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (*dst && i < size)
	{
		dst++;
		i++;
	}
	i += ft_strlcpy(dst, src, size - i);
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}
