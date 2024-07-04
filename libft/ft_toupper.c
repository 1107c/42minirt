/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:20:02 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/28 16:47:31 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	else
		return (c);
}
/*
#include <stdio.h>
#include <ctype.h>
int main ()
{
	printf("%d\n", ft_toupper('a'));
	printf("%d\n", ft_toupper('A'));
	printf("%d\n", ft_toupper('@'));
	printf("\n");
	printf("%d\n", toupper('a'));
	printf("%d\n", toupper('A'));
	printf("%d\n", toupper('@'));
}*/