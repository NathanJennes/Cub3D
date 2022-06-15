/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_worker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:41:11 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 18:46:03 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"

inline static t_bool	is_game_running(void);
inline static void		init_cols(int64_t *col_start, int64_t *col_end, int64_t id);

void	*renderer_worker_loop(void *param_id)
{
	int64_t			id;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*working_lock;
	int64_t			col_start;
	int64_t			col_end;
	t_renderer		*renderer;

	id = (int64_t)param_id;
	renderer = &get_app()->renderer;
	lock = &renderer->locks[id];
	working_lock = &renderer->working_lock[id];
	init_cols(&col_start, &col_end, id);
	while (is_game_running())
	{
		pthread_mutex_lock(working_lock);
		pthread_mutex_lock(lock);
		pthread_mutex_unlock(working_lock);
		render_walls(col_start, col_end);
		pthread_mutex_unlock(lock);
	}
	return (EXIT_SUCCESS);
}

inline static t_bool	is_game_running(void)
{
	t_renderer	*renderer;
	t_bool		running;

	renderer = &get_app()->renderer;
	pthread_mutex_lock(&renderer->running_lock);
	running = renderer->running;
	pthread_mutex_unlock(&renderer->running_lock);
	return (running);
}

inline static void		init_cols(int64_t *col_start, int64_t *col_end, int64_t id)
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
