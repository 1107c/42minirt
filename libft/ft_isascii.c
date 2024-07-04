/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:07:15 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/28 17:34:28 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int main ()
{
	printf("%d\n", ft_isascii(0));
    printf("%d\n", ft_isascii(-1));
    printf("%d\n", ft_isascii(-2147483648));
    printf("%d\n", ft_isascii(2147483647));
	printf("%d\n", ft_isascii(127));
	printf("%d\n", ft_isascii(128));
    printf("\n");
	printf("%d\n", isascii(0));
    printf("%d\n", isascii(-1));
    printf("%d\n", isascii(-2147483649));
    printf("%d\n", isascii(2147483648));
	printf("%d\n", isascii(127));
	printf("%d\n", isascii(128));
}*/