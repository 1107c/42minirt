/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:57:43 by myeochoi          #+#    #+#             */
/*   Updated: 2024/03/01 20:23:49 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *dest, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = dest;
	i = 0;
	while (i < n)
		p[i++] = 0;
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
	char arr[] = "blockdmask";
	bzero(arr, 5 * sizeof(char));
	printf("%s\n",arr);
	ft_bzero(arr, 5 * sizeof(char));
	printf("%s\n",arr);
}*/