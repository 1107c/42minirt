/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:16:56 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/15 18:16:56 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	mul_vec(t_vec lhs, double rhs)
{
	return ((t_vec){lhs.x * rhs, lhs.y * rhs, lhs.z * rhs});
}
