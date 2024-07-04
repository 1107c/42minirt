/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:57:10 by myeochoi          #+#    #+#             */
/*   Updated: 2024/07/04 13:35:44 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

int	print_err(t_msg	msg)
{
	if (msg == NO_ARG)
		return (ft_putendl_fd("no input, enter the *.rt file or with \
--save option.", 1) , 1);
	if (msg == MUCH_ARG)
		return (ft_putendl_fd("too many input, enter the *.rt file or with \
--save option.", 1) , 1);
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}


int	minirt_err_control(int arg, char **args)
{


	
}

int	main(int arg, char **args)
{
	if (arg == 1)
		return (print_err(NO_ARG));
	else if (arg > 3)
		return (print_err(NO_ARG));
	else
	{
		if (minirt_err_control(arg, args))
			return (1);
		// else
		// 	minirt();
	}
	return (0);
}