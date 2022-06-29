/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:36:31 by njennes           #+#    #+#             */
/*   Updated: 2022/06/29 15:45:32 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "core.h"
#include "render.h"
#include "leaky.h"

inline static void		render_multithreaded(t_renderer *renderer);
inline static void		render_singlethreaded(void);

void	init_renderer(t_bool init_threads)
{
	int64_t		i;
	t_renderer	*renderer;

	renderer = &get_app()->renderer;
	renderer->depth_buffer = gc_calloc(get_settings()->win_w, sizeof (double));
	ft_memsetd(renderer->depth_buffer, DBL_MAX, get_settings()->win_w);
	renderer->running = TRUE;
	renderer->multithreading = FALSE;
	if (init_threads)
	{
		pthread_mutex_init(&renderer->running_lock, NULL);
		i = 0;
		while (i < RENDER_WORKER_COUNT)
		{
			pthread_mutex_init(&renderer->locks[i], NULL);
			pthread_mutex_init(&renderer->working_lock[i], NULL);
			pthread_mutex_lock(&renderer->locks[i]);
			pthread_create(&renderer->workers[i], NULL,
				renderer_worker_loop, (void *)i);
			pthread_detach(renderer->workers[i]);
			i++;
		}
	}
}

void	shutdown_renderer(void)
{
	size_t		i;
	t_renderer	*renderer;

	renderer = &get_app()->renderer;
	i = 0;
	pthread_mutex_lock(&renderer->running_lock);
	renderer->running = FALSE;
	pthread_mutex_unlock(&renderer->running_lock);
	while (i < RENDER_WORKER_COUNT)
	{
		pthread_join(renderer->workers[i], NULL);
		pthread_mutex_destroy(&renderer->locks[i]);
		pthread_mutex_destroy(&renderer->working_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&renderer->running_lock);
}

void	renderer_render(void)
{
	t_renderer	*renderer;

	renderer = &get_app()->renderer;
	ft_memsetd(renderer->depth_buffer, DBL_MAX, get_settings()->win_w);
	if (renderer->multithreading)
		render_multithreaded(renderer);
	else
		render_singlethreaded();
}

inline static void	render_multithreaded(t_renderer *renderer)
{
	int64_t	i;

	i = 0;
	while (i < RENDER_WORKER_COUNT)
		pthread_mutex_unlock(&renderer->locks[i++]);
	i = 0;
	while (i < RENDER_WORKER_COUNT)
		pthread_mutex_lock(&renderer->working_lock[i++]);
	i = 0;
	while (i < RENDER_WORKER_COUNT)
		pthread_mutex_lock(&renderer->locks[i++]);
	i = 0;
	while (i < RENDER_WORKER_COUNT)
		pthread_mutex_unlock(&renderer->working_lock[i++]);
}

inline static void	render_singlethreaded(void)
{
	render_walls(0, get_settings()->win_w - 1);
}
