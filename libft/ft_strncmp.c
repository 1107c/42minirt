/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:28:59 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/29 13:24:41 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((unsigned char)s1[i] == (unsigned char)s2[i]) && s1[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include<stdio.h>
#include<string.h>
int main()
{
	char s1[] = "asd";
	char s2[]  = "asdf";
	printf("%d\n%d\n", strncmp(s1,s2, 4), ft_strncmp(s1,s2,4));
	char s3[] = "asdfa";
	char s4[]  = "asdfc";
	printf("%d\n%d\n", strncmp(s3,s4, 4), ft_strncmp(s3,s4,4));
	char s5[] = "fasd";
	char s6[]  = "asdf";
	printf("%d\n%d\n", strncmp(s5,s6, 6), ft_strncmp(s5,s6,6));
}*/