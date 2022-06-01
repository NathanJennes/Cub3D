/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 18:34:17 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "core.h"
#include "ui.h"
#include "render.h"

void	render_test_scene(const t_mlx *app);

int	main_loop(void)
{
	t_mlx		*app;
	t_settings	*settings;
	struct timeval time[4];

	app = get_app();
	settings = get_settings();
	update_player(&app->gamestate.player);
	if (app->app_state & IN_GAME)
	{
		gettimeofday(&time[0], NULL);
		draw_rect_unsafe(ivec2(0, 0), ivec2(settings->win_w, settings->halfw_h), CEILLING);
		draw_rect_unsafe(ivec2(0, settings->halfw_h), ivec2(settings->win_w, settings->halfw_h), FLOOR);
		mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
		gettimeofday(&time[1], NULL);
		renderer_render();
		gettimeofday(&time[2], NULL);
		render_test_scene(app);
		gettimeofday(&time[3], NULL);
		if (app->ui.debug_ui == TRUE)
			printf("[FRAME - RENDER]: background: %lldms, walls: %lldms, test_scene: %lldms, total %lldms\n",
				(int64_t)((time[1].tv_sec * 1000 + time[1].tv_usec / 1000) - (time[0].tv_sec * 1000 + time[0].tv_usec / 1000)),
				(int64_t)((time[2].tv_sec * 1000 + time[2].tv_usec / 1000) - (time[1].tv_sec * 1000 + time[1].tv_usec / 1000)),
				(int64_t)((time[3].tv_sec * 1000 + time[3].tv_usec / 1000) - (time[2].tv_sec * 1000 + time[2].tv_usec / 1000)),
				(int64_t)((time[3].tv_sec * 1000 + time[3].tv_usec / 1000) - (time[0].tv_sec * 1000 + time[0].tv_usec / 1000)));
	}
	else
		clear_screen(BKGD_COLOR);
	if (app->ui.debug_ui == TRUE)
		print_debug();
	fps_counter();
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	update_ui();
	render_ui();
	return (0);
}
