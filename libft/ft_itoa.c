/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:42:53 by ksuh              #+#    #+#             */
/*   Updated: 2024/02/29 20:54:37 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoasize(unsigned int n);

char	*ft_itoa(int n)
{
	unsigned int	i;
	char			*dest;
	size_t			destidx;
	size_t			len;

	if (n == 0)
		return (ft_strdup("0"));
	i = n;
	if (n < 0)
		i = (unsigned int)-n;
	len = ft_itoasize(i);
	destidx = len + (n < 0);
	dest = (char *)malloc((destidx + 1) * sizeof(char));
	if (!dest)
		return (0);
	if (n < 0)
		dest[0] = '-';
	dest[destidx--] = '\0';
	while (i > 0)
	{
		dest[destidx--] = '0' + i % 10;
		i /= 10;
	}
	return (dest);
}

size_t	ft_itoasize(unsigned int n)
{
	size_t	m;

	m = 0;
	while (n > 0)
	{
		m++;
		n /= 10;
	}
	return (m);
}
