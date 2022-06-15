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

static t_ivec2	debug_player(t_ivec2 *pos);
static void		debug_rays(t_ivec2 *pos);
static t_ivec2	debug_settings(t_ivec2 *pos);

void	print_debug(void)
NOPROF
{
	t_ivec2	debug_pos;

	debug_pos = ivec2(20, get_settings()->win_h / 2 - 100);
	debug_rays(&debug_pos);
	debug_pos.y += 20;
	debug_player(&debug_pos);
	debug_pos.y += 40;
	debug_settings(&debug_pos);
	debug_pos.y += 40;
	if (get_app()->renderer.multithreading)
	{
		render_text("multithreaded", DEFAULT_FONT, 20,
		text_center_height("singlethreaded", DEFAULT_FONT, 20,
			ivec2(debug_pos.x, debug_pos.y)));
	}
	else
	{
		render_text("singlethreaded", DEFAULT_FONT, 20,
		text_center_height("singlethreaded", DEFAULT_FONT, 20,
			ivec2(debug_pos.x, debug_pos.y)));
	}
}

static void	debug_rays(t_ivec2 *pos)
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

static t_ivec2	debug_player(t_ivec2 *pos)
NOPROF
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
	print_ivec2(get_mouse_position(), DEFAULT_FONT, 15,
			ivec2(pos->x + str_px_size("Mouse pos ") + 25, pos->y));
	pos->y += 10;
}

static t_ivec2	debug_settings(t_ivec2 *pos)
NOPROF
{
	render_text("Settings", DEFAULT_FONT, 15, ivec2(pos->x, pos->y));
	pos->y += 20;
	render_text("FOV ", DEFAULT_FONT, 15, ivec2(pos->x, pos->y));
	print_int(get_settings()->fov, DEFAULT_FONT, 15,
		ivec2(pos->x + str_px_size("FOV ") + 25, pos->y));
}
