/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:36:18 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/20 17:20:06 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "core.h"
#include "leaky.h"
#include "ui.h"
#include "colors.h"

static int64_t	get_sec_time(void);

void	fps_counter(void)
{
	t_mlx		*app;
	static int	nbr_frames;
	static int	last_fps;
	char		*fps;
	int64_t		current_time;

	app = get_app();
	nbr_frames++;
	current_time = get_sec_time();
	if ((current_time - app->start_time) >= 1)
	{
		fps = gc_itoa(nbr_frames);
		last_fps = nbr_frames;
		nbr_frames = 0;
		app->start_time = current_time;
	}
	else
		fps = gc_itoa(last_fps);
	put_text(ivec2(WIN_W - str_px_size(fps) - 10, 15), WHITE, fps);
	gc_free(fps);
}

static int64_t	get_sec_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec);
}
