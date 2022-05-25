/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/25 19:46:47 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

void	render_test_scene(const t_mlx *app);

int	main_loop(void)
{
	t_mlx	*app;

	app = get_app();
	update_player(&app->gamestate.player);
	clear_screen(BKGD_COLOR);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	if (app->game_state & IN_GAME)
	{
		draw_rect(ivec2(0, 0), ivec2(WIN_W, WIN_H / 2), CEILLING);
		draw_rect(ivec2(0, WIN_H / 2), ivec2(WIN_W, WIN_H / 2), FLOOR);
		render_walls();
		render_test_scene(app);
	}
	if (app->ui.debug_ui == TRUE)
		print_debug();
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	update_ui();
	render_ui();
	return (0);
}
