/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:18 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/01 15:03:20 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "core.h"
#include "leaky.h"
#include "ui.h"
#include "render.h"

static int64_t	get_time(void);

void display_fps(int64_t time_diff);

void	fps_counter(void)
{
	t_mlx		*app;
	int64_t		current_time;
	int64_t		time_diff;

	app = get_app();
	current_time = get_time();
	time_diff = current_time - app->last_time;
	app->last_time = current_time;
	app->delta_time = (double)time_diff / 1000.0;
	if (app->ui.debug_ui == TRUE)
		display_fps(time_diff);
}

void display_fps(int64_t time_diff)
{
	static int64_t	elapsed;
	static char		*fps;
	static char		*ms;

	if (elapsed > 500 || !fps || !ms)
	{
		gc_free(fps);
		gc_free(ms);
		fps = gc_itoa((int)(1000 / time_diff));
		ms = gc_itoa((int)time_diff);
		ms = gc_strjoin(ms, " ms", FREE_FIRST);
		elapsed -= 500;
	}
	render_text(fps, DEFAULT_FONT, 20,
		text_center_width(fps, DEFAULT_FONT, 20, ivec2(get_settings()->win_w - str_px_size(fps) - 10, 15)));
	render_text(ms, DEFAULT_FONT, 20,
		text_center_width(ms, DEFAULT_FONT, 20, ivec2(get_settings()->win_w - str_px_size(ms) - 10, 35)));
	elapsed += time_diff;
}

static int64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
