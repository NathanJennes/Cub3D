/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 17:04:47 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

void	render_test_scene(const t_mlx *app);

int	main_loop(void)
{
	t_mlx		*app;
	t_settings	*settings;

	app = get_app();
	settings = get_settings();
	update_player(&app->gamestate.player);
	if (app->app_state & IN_GAME)
	{
		draw_rect_unsafe(ivec2(0, 0), ivec2(settings->win_w, settings->halfw_h), CEILLING);
		draw_rect_unsafe(ivec2(0, settings->halfw_h), ivec2(settings->win_w, settings->halfw_h), FLOOR);
		mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
		renderer_render();
		render_test_scene(app);
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
