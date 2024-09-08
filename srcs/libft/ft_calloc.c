/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:09:52 by ksuh              #+#    #+#             */
/*   Updated: 2024/03/01 20:25:36 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*dest;

	if (!n || !size)
		return (ft_strdup(""));
	dest = malloc(n * size);
	if (!dest)
		return (0);
	ft_bzero(dest, n * size);
	return (dest);
}
