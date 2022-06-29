/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:44:35 by njennes           #+#    #+#             */
/*   Updated: 2022/06/29 16:55:10 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

inline static void		render_game(t_mlx *app, const t_settings *settings);

int	main_loop(void)
{
	t_mlx			*app;
	t_settings		*settings;

	app = get_app();
	settings = get_settings();
	update_player(&app->gamestate.player, TRUE);
	reset_mouse_pos();
	render_game(app, settings);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	return (0);
}

inline static void	render_game(t_mlx *app, const t_settings *settings)
{
	draw_rect_unsafe(ivec2(0, 0),
		ivec2(settings->win_w, settings->halfw_h),
		get_map_infos()->ceiling.color);
	draw_rect_unsafe(ivec2(0, settings->halfw_h),
		ivec2(settings->win_w, settings->halfw_h),
		get_map_infos()->floor.color);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	renderer_render();
}
