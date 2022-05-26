/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/26 16:41:03 by njennes          ###   ########.fr       */
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
	if (app->game_state & IN_GAME)
	{
		render_ui_texture(app->ceiling_tex, 0, 0);
		render_ui_texture(app->floor_tex, 0, WIN_H / 2);
		render_walls();
		render_test_scene(app);
	}
	else
	{
		clear_screen(BKGD_COLOR);
		mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	}
	if (app->ui.debug_ui == TRUE)
		print_debug();
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	update_ui();
	render_ui();
	return (0);
}
