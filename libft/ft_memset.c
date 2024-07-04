/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:44:21 by myeochoi          #+#    #+#             */
/*   Updated: 2024/03/01 20:24:24 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*p;
	size_t			i;

	p = ptr;
	i = 0;
	while (i < num)
		p[i++] = (unsigned char)value;
	return ((void *)p);
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
	char arr[] = "blockdmask";
	memset(arr, 'c', 5 * sizeof(char));
	printf("%s\n",arr);
	ft_memset(arr, 'c', 5 * sizeof(char));
	printf("%s\n",arr);
}*/