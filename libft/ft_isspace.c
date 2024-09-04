/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:21:24 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/04 15:33:06 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<< HEAD:main.c
#include "minirt.h"
// 김시윤의 작품
static int	close_win(t_rt *rt);

int	main(int argc, char **argv)
=======
#include "libft.h"

int	ft_isspace(int c)
>>>>>>> a08a6248780b5600196a0ab07ed200c10aa98397:libft/ft_isspace.c
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
