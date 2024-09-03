/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:55:55 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/03 11:23:25 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ◦ Each type of element can be separated by one or more line break(s).
// ◦ Each type of information from an element can be separated by one or more space(s).
// ◦ Each type of element can be set in any order in the file.
// ◦ Elements which are defined by a capital letter can only be declared once in the scene.

// 1. 각각의 요소들은 하나 이상의 개행으로 구분되어야 함
// 2. 요소 각각의 정보들은 하나 이상의 공백으로 구분되어야 함
// 3. 순서는 상관없이
// 4. 도형을 제외한 A, C, L(영어 대문자로 구성된 요소)들은 단 한번만 나와야 합니다.


void	interpret_data(t_rt *rt)
{
	char	*line;

	printf("fd: %d\n", rt->file_fd);
	while (1)
	{
		line = get_next_line(rt->file_fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close(rt->file_fd);
}
