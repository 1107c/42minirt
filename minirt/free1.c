/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:01:53 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/14 19:01:53 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_obj(t_object **to)
{
	t_object	*tmp;
	t_object	*obj;

	obj = *to;
	while (obj)
	{
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
	*to = 0;
}

void	free_light(t_light **tl)
{
	t_light	*tmp;
	t_light	*light;

	light = *tl;
	while (light)
	{
		tmp = light;
		light = light->next;
		free(tmp);
	}
	*tl = 0;
}

char	**ft_free(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (0);
}

//void	ft_2dfree(char **s)
//{
//	size_t	i;

//	i = 0;
//	if (s)
//	{
//		while (s[i])
//		{
//			free(s[i]);
//			i++;
//		}
//		free(s);
//	}
//}
