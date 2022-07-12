/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:16:28 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/15 16:00:22 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

inline static void	debug_player(t_ivec2 *pos);
inline static void	debug_rays(t_ivec2 *pos);
inline static void	debug_settings(t_ivec2 *pos);

void	print_debug(void)
{
	t_ivec2	debug_pos;

	if (get_ui()->debug_state == NO_DEBUG)
		return ;
	debug_pos = ivec2(20, get_settings()->win_h / 2);
	debug_rays(&debug_pos);
	debug_pos.y += 20;
	debug_player(&debug_pos);
	debug_pos.y += 40;
	debug_settings(&debug_pos);
	if (get_app()->renderer.multithreading)
	{
		render_text("multithreaded", DEFAULT_FONT, 20,
			text_center_height("singlethreaded", DEFAULT_FONT, 20,
				ivec2(get_settings()->win_w - 200, debug_pos.y)));
	}
	else
	{
		render_text("singlethreaded", DEFAULT_FONT, 20,
			text_center_height("singlethreaded", DEFAULT_FONT, 20,
				ivec2(get_settings()->win_w - 200, debug_pos.y)));
	}
}

inline static void	debug_rays(t_ivec2 *pos)
{
	t_player	*player;

	player = get_player();
	render_text("Ray angle ", DEFAULT_FONT, 15, ivec2(pos->x, pos->y));
	print_double(get_math()->base_angle, DEFAULT_FONT, 15,
		ivec2(pos->x + str_px_size("Ray angle ") + 30, pos->y));
	pos->y += 20;
	render_text("Plane increment ", DEFAULT_FONT, 15, ivec2(pos->x, pos->y));
	print_vec2(player->plane_inc, DEFAULT_FONT, 15,
		ivec2(pos->x + str_px_size("Plane increment ") + 25, pos->y));
	pos->y += 40;
}

inline static void	debug_player(t_ivec2 *pos)
{
	t_player	*player;

	player = get_player();
	render_text("Direction ", DEFAULT_FONT, 15, ivec2(pos->x, pos->y));
	print_double(player->direction, DEFAULT_FONT, 15,
		ivec2(pos->x + str_px_size("Direction ") + 25, pos->y));
	pos->y += 20;
	render_text("World pos ", DEFAULT_FONT, 15, ivec2(pos->x, pos->y));
	print_vec2(player->world_pos, DEFAULT_FONT, 15,
		ivec2(pos->x + str_px_size("World pos ") + 25, pos->y));
	pos->y += 20;
	render_text("Grid pos ", DEFAULT_FONT, 15, ivec2(pos->x, pos->y));
	print_vec2(player->cell_pos, DEFAULT_FONT, 15,
		ivec2(pos->x + str_px_size("Grid pos ") + 25, pos->y));
	pos->y += 20;
	render_text("Map pos ", DEFAULT_FONT, 15, ivec2(pos->x, pos->y));
	print_ivec2(player->map_pos, DEFAULT_FONT, 15,
		ivec2(pos->x + str_px_size("Map pos ") + 25, pos->y));
	pos->y += 40;
	render_text("Mouse pos ", DEFAULT_FONT, 15, ivec2(pos->x, pos->y));
	print_ivec2(get_mouse_pos(), DEFAULT_FONT, 15,
		ivec2(pos->x + str_px_size("Mouse pos ") + 25, pos->y));
	pos->y += 10;
}

inline static void	debug_settings(t_ivec2 *pos)
{
	render_text("Settings", DEFAULT_FONT, 15, ivec2(pos->x, pos->y));
	pos->y += 20;
	render_text("FOV ", DEFAULT_FONT, 15, ivec2(pos->x, pos->y));
	print_int(get_settings()->fov, DEFAULT_FONT, 15,
		ivec2(pos->x + str_px_size("FOV ") + 25, pos->y));
}

void	debug_time_frame(const t_mlx *app, struct timeval *time)
{
	if (app->ui.debug_state == LVL2)
		printf("[FRAME - RENDER]: background: %lldms, walls: "
			"%lldms, test_scene: %lldms, total %lldms\n",
			(int64_t)((time[1].tv_sec * 1000 + time[1].tv_usec / 1000)
				- (time[0].tv_sec * 1000 + time[0].tv_usec / 1000)),
			(int64_t)((time[2].tv_sec * 1000 + time[2].tv_usec / 1000)
				- (time[1].tv_sec * 1000 + time[1].tv_usec / 1000)),
			(int64_t)((time[3].tv_sec * 1000 + time[3].tv_usec / 1000)
				- (time[2].tv_sec * 1000 + time[2].tv_usec / 1000)),
			(int64_t)((time[3].tv_sec * 1000 + time[3].tv_usec / 1000)
				- (time[0].tv_sec * 1000 + time[0].tv_usec / 1000)));
}
