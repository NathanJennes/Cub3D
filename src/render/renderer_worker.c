/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_worker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:41:11 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 17:02:21 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"

static t_bool	is_game_running(void);
static void		init_cols(int64_t *col_start, int64_t *col_end, int64_t id);

void	*renderer_worker_loop(void *param_id)
{
	int64_t			id;
	pthread_mutex_t	*lock;
	int64_t			col_start;
	int64_t			col_end;

	id = (int64_t)param_id;
	lock = &get_app()->renderer.locks[id];
	init_cols(&col_start, &col_end, id);
	while (is_game_running())
	{
		pthread_mutex_lock(lock);
		render_walls(col_start, col_end);
		pthread_mutex_unlock(lock);
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

static t_bool	is_game_running(void)
{
	t_renderer	*renderer;
	t_bool		running;

	renderer = &get_app()->renderer;
	pthread_mutex_lock(&renderer->running_lock);
	running = renderer->running;
	pthread_mutex_unlock(&renderer->running_lock);
	return (running);
}

static void		init_cols(int64_t *col_start, int64_t *col_end, int64_t id)
{
	int64_t		section;
	t_settings	*settings;

	settings = get_settings();
	section = settings->win_w / RENDER_WORKER_COUNT;
	*col_start = section * id;
	if (id == RENDER_WORKER_COUNT - 1)
		*col_end = settings->win_w - 1;
	else
		*col_end = section * (id + 1) - 1;
}
