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
	h = WINDOW_HEIGHT / NUM_THREADS;
	while (i < NUM_THREADS)
	{
		workers[i].y_start = start;
		start += h;
		start += (3 - start % 3) % 3;
		workers[i].y_end = start;
		workers[i].rt = rt;
		i++;
	}
	workers[NUM_THREADS - 1].y_end = WINDOW_HEIGHT;
}

void	thread_work(t_worker *workers)
{
	pthread_t	threads[NUM_THREADS];
	int			i;

	i = -1;
	while (++i < NUM_THREADS)
	{
		if (workers->rt->fast == -1)
			pthread_create(&threads[i], NULL, \
							render_scene, &workers[i]);
		else
			pthread_create(&threads[i], NULL, \
							render_scene_fast, &workers[i]);
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], NULL);
}
