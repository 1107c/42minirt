/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:07:31 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/28 17:34:32 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int main ()
{
	printf("%d\n", ft_isprint(31));
	printf("%d\n", ft_isprint(32));
	printf("%d\n", ft_isprint(127));
    printf("\n");
	printf("%d\n", isprint(31));
	printf("%d\n", isprint(32));
	printf("%d\n", isprint(127));
}*/
