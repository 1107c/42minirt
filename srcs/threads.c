/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:52:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/21 13:52:46 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	init_workers(t_worker *workers, t_rt *rt)
{
	int	i;
	int	start;
	int	h;

	i = 0;
	start = 0;
	h = WINDOW_HEIGHT / THREADS_NUM;
	while (i < THREADS_NUM)
	{
		workers[i].y_start = start;
		start += h;
		workers[i].y_end = start;
		workers[i].rt = rt;
		i++;
	}
	workers[THREADS_NUM - 1].y_end = WINDOW_HEIGHT;
}

void	thread_work(t_worker *workers)
{
	pthread_t	threads[THREADS_NUM];
	int			i;

	i = -1;
	while (++i < THREADS_NUM)
		pthread_create(&threads[i], NULL, render_scene, &workers[i]);
	i = -1;
	while (++i < THREADS_NUM)
		pthread_join(threads[i], NULL);
}
