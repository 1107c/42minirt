/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:25:59 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/08 12:25:59 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static size_t	ft_count_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		len;
	char		**ret;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s != c && *s && ++len)
				s++;
			ret[i] = ft_substr(s - len, 0, len);
			if (!ret[i++])
				return (ft_free(ret));
		}
		else
			s++;
	}
	ret[i] = 0;
	return (ret);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_double_range(double d, double range_min, double range_max)
{
	return (d >= range_min && d <= range_max);
}
