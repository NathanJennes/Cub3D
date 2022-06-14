/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:16:28 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/08 11:17:26 by Cyril            ###   ########.fr       */
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
	put_text(ivec2(pos->x, pos->y), WHITE, "Ray angle ");
	print_float(get_math()->base_angle,
		ivec2(pos->x + str_px_size("Ray angle "), pos->y), WHITE);
	pos->y += 20;
	put_text(ivec2(pos->x, pos->y), WHITE, "Ray increment ");
	print_vec(player->plane_inc,
		ivec2(pos->x + str_px_size("Plane increment "), pos->y), WHITE);
	pos->y += 20;
}

static t_ivec2	debug_player(t_ivec2 *pos)
NOPROF
{
	t_player	*player;

	player = get_player();
	put_text(ivec2(pos->x, pos->y), WHITE, "Direction ");
	print_float(player->direction,
		ivec2(pos->x + str_px_size("Direction "), pos->y), WHITE);
	pos->y += 20;
	put_text(ivec2(pos->x, pos->y), WHITE, "World pos ");
	print_vec(player->world_pos,
		ivec2(pos->x + str_px_size("World pos "), pos->y), WHITE);
	pos->y += 20;
	put_text(ivec2(pos->x, pos->y), WHITE, "Grid pos ");
	print_vec(player->cell_pos,
		ivec2(pos->x + str_px_size("Grid pos "), pos->y), WHITE);
	pos->y += 20;
	put_text(ivec2(pos->x, pos->y), WHITE, "Map pos ");
	print_ivec(player->map_pos,
		ivec2(pos->x + str_px_size("Map pos "), pos->y), WHITE);
	pos->y += 20;
	put_text(ivec2(pos->x, pos->y), WHITE, "Mouse pos ");
	print_ivec(get_mouse_position(),
		ivec2(pos->x + str_px_size("Mouse pos "), pos->y), WHITE);
}

static t_ivec2	debug_settings(t_ivec2 *pos)
NOPROF
{
	put_text(ivec2(pos->x, pos->y), WHITE, "Settings");
	pos->y += 20;
	put_text(ivec2(pos->x, pos->y), WHITE, "FOV ");
	print_int(get_settings()->fov,
		ivec2(pos->x + str_px_size("FOV "), pos->y), WHITE);
}
