/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:17:44 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/28 16:47:31 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}
/*
#include <stdio.h>
#include <ctype.h>
int main ()
{
	printf("%d\n", ft_tolower('a'));
	printf("%d\n", ft_tolower('A'));
	printf("%d\n", ft_tolower('@'));
	printf("\n");
	printf("%d\n", tolower('a'));
	printf("%d\n", tolower('A'));
	printf("%d\n", tolower('@'));
}*/