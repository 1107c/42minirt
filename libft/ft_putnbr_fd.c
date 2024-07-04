/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:09:12 by myeochoi          #+#    #+#             */
/*   Updated: 2024/02/29 15:26:32 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_write_itoa(int n, int fd, int i, int j)
{
	size_t	x;
	int		c;

	x = 1;
	while ((size_t)n >= x)
	{
		x *= 10;
		i++;
	}
	x /= 10;
	while (j < i)
	{
		c = (n / x) + 48;
		write(fd, &c, 1);
		n -= (n / x) * x;
		x /= 10;
		j++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0 && n > -2147483648)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	ft_write_itoa(n, fd, 0, 0);
}
/*
void ft_putnbr(int n)
{
	int	i;
	int	c;
	size_t x;
	int j;

	x = 1;
	i = 0;
	j = 0;
	if (n < 0 && n > -2147483648)
	{
		write(1, "-", 1);
		n *= -1;
	}
	while ((size_t)n >= x)
	{
		x *= 10;
		i++;
	}
	x /= 10;
	while (j < i)
	{
		c = (n / x) + 48;
		write(1, &c, 1);
		n -= (n / x) * x;
		x /= 10;
		j++;
	}
}
int main()
{
	ft_putnbr(-2147483648);
	write(1,"\n",1);
	ft_putnbr(-2147483647);
	write(1,"\n",1);
	ft_putnbr(2147483647);
	write(1,"\n",1);
	ft_putnbr(0);
	write(1,"\n",1);
	ft_putnbr(1000);
}*/