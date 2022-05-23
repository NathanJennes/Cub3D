/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/05/23 15:58:24 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

int	main_loop(void)
{
	t_mlx	*app;

	app = get_app();
	if (app->game_state & IN_GAME)
	{
	}
	clear_screen(BKGD_COLOR);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	t_ivec2 center = ivec2(WIN_W / 2, WIN_H / 2);

	t_ivec2 text_size = get_text_size("ceci est un text!", "HelveticaNeue", cub_get_mouse_position().y / 2);
	draw_circle(ivec2(center.x - text_size.x / 2, center.y - text_size.y / 2), 20, trgb(0, 255, 0, 0));
	draw_rect(ivec2(center.x - text_size.x / 2, center.y - text_size.y / 2), text_size, trgb(0, 51, 51, 51));

	t_ivec2 text_pos = text_center("ceci est un text!", "HelveticaNeue", cub_get_mouse_position().y / 2, center);

	draw_circle(text_pos, 20, trgb(0, 0, 255, 0));
	draw_circle(center, 20, trgb(0, 0, 0, 255));
	render_text("ceci est un text!", "HelveticaNeue", cub_get_mouse_position().y / 2, text_pos);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	//update_ui();
	//render_ui();
	return (0);
}
