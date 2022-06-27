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
inline static void	init_cols(t_ivec2 *col, int64_t id);

void	*renderer_worker_loop(void *param_id)
{
	int64_t			id;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*working_lock;
	t_ivec2			col;
	t_renderer		*renderer;

	id = (int64_t)param_id;
	renderer = &get_app()->renderer;
	lock = &renderer->locks[id];
	working_lock = &renderer->working_lock[id];
	init_cols(&col, id);
	while (is_game_running())
	{
		pthread_mutex_lock(working_lock);
		pthread_mutex_lock(lock);
		pthread_mutex_unlock(working_lock);
		render_walls(col.x, col.y);
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

inline static void	init_cols(t_ivec2 *col, int64_t id)
{
	int64_t		section;
	t_settings	*settings;

	settings = get_settings();
	section = settings->win_w / RENDER_WORKER_COUNT;
	col->x = section * id;
	if (id == RENDER_WORKER_COUNT - 1)
		col->y = settings->win_w - 1;
	else
		col->y = section * (id + 1) - 1;
}
