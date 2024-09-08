/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:29:17 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/03 14:37:35 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_memlen(char const *s, int (*f)(int));
static char		*ft_splitalloc(char const **s, int (*f)(int));
static void		ft_splitfree(char ***dest, size_t idx);

char	**ft_split(char const *s, int (*f)(int))
{
	char	**dest;
	size_t	len;
	size_t	destidx;

	len = ft_memlen(s, (*f));
	dest = (char **)malloc((len + 1) * sizeof(char *));
	if (!dest)
		return (0);
	destidx = 0;
	while (destidx < len)
	{
		dest[destidx] = ft_splitalloc(&s, (*f));
		if (!dest[destidx])
		{
			ft_splitfree(&dest, destidx);
			return (0);
		}
		destidx++;
	}
	dest[destidx] = 0;
	return (dest);
}

void	ft_splitfree(char ***dest, size_t idx)
{
	size_t	m;

	m = 0;
	while (m < idx)
		free(*dest[m++]);
	free(*dest);
}

char	*ft_splitalloc(char const **s, int (*f)(int))
{
	size_t	m;
	char	*res;

	m = 0;
	while (**s && f(**s))
		(*s)++;
	while (*(*s + m) && !f(*(*s + m)))
		m++;
	res = ft_substr(*s, 0, m);
	*s += m;
	return (res);
}

size_t	ft_memlen(char const *s, int (*f)(int))
{
	size_t	m;

	m = 0;
	while (*s)
	{
		while (*s && f(*s))
			s++;
		if (*s)
		{
			while (*s && !f(*s))
				s++;
			m++;
		}
	}
	return (m);
}
