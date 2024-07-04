/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:29:52 by myeochoi          #+#    #+#             */
/*   Updated: 2024/03/01 20:23:56 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*s1;
	size_t			t_size;

	t_size = size * nmemb;
	s1 = malloc(t_size);
	if (s1 == 0)
		return (0);
	ft_bzero(s1, t_size);
	return ((void *)s1);
}
/*
#include <stdio.h>
#include <stdlib.h>

int main() {
	char *arr_1;
	char *arr_2;
	int *arr_3;
	int i;

	arr_1 = (char *) calloc(5, sizeof(char) + 1);
	arr_2 = (char *) malloc(sizeof((char) + 1) * 5);
	arr_3 = (int *) ft_calloc(5, sizeof(int) + 1);
	i = 0;
	while (i < 5)
		printf("%d\n",  arr_1[i++]);
	printf("\n");
	i = 0;
	while (i < 5)
		printf("%d\n",  arr_2[i++]);
	printf("\n");
	i = 0;
	while (i < 5)
		printf("%d\n",  arr_3[i++]);
	free(arr_1);
	free(arr_2);
	free(arr_3);
	return 0;
}*/