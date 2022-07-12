/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main_menu_background.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:06:30 by njennes           #+#    #+#             */
/*   Updated: 2022/06/20 19:34:26 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"

void				change_background(t_mlx *app);
inline static void		setup_camera(t_mlx *app);

void	render_main_menu_background(void)
{
	static int		dir = 1;
	static double	time = 5;
	t_mlx			*app;
	t_settings		*settings;

	app = get_app();
	settings = get_settings();
	time += app->delta_time;
	if (time > 4)
	{
		dir = dir * -1;
		change_background(app);
		time = 0;
	}
	app->gamestate.player.direction += app->delta_time / 5.0 * dir;
	update_player_direction(&app->gamestate.player, app->delta_time, FALSE);
	update_player_vectors(&app->gamestate.player);
	draw_rect_unsafe(ivec2(0, 0),
		ivec2(settings->win_w, settings->halfw_h),
		get_map_infos()->ceiling.color);
	draw_rect_unsafe(ivec2(0, settings->halfw_h),
		ivec2(settings->win_w, settings->halfw_h),
		get_map_infos()->floor.color);
	renderer_render();
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
}

void	change_background(t_mlx *app)
{
	int	new_map;

	new_map = rand() % app->maps_count;
	app->gamestate = app->maps[new_map];
	setup_camera(app);
}

inline static void	setup_camera(t_mlx *app)
{
	t_ivec2		cam_pos;
	t_map_info	*infos;

	infos = &app->gamestate.map;
	cam_pos = ivec2(rand() % infos->width, rand() % infos->height);
	while (infos->map[cam_pos.y][cam_pos.x] == WALL ||
		infos->map[cam_pos.y][cam_pos.x] == VOID)
		cam_pos = ivec2(rand() % infos->width, rand() % infos->height);
	app->gamestate.player.world_pos = \
		vec2(cam_pos.x * CELL_SIZE + CELL_SIZE / 2,
			cam_pos.y * CELL_SIZE + CELL_SIZE / 2);
	app->gamestate.player.direction = \
		(double)(rand() % 4) + (double)(rand() % 10) / 10.0;
}
