/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:45:59 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 10:27:08 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *s, long long range_min, long long range_max)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while ((*s >= '\t' && *s <= '\r') || *s == ' ')
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s++ == '-')
			sign = -1;
	}
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		if (sign == -1 && res * sign < range_min)
			break ;
		else if (sign == 1 && res > range_max)
			break ;
		s++;
	}
	return (sign * res);
}
