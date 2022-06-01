/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:16:28 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/01 14:20:33 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"

static void	debug_player(void);

void	print_debug(void)
NOPROF
{
	fps_counter();
	debug_player();
}

static void	debug_player(void)
NOPROF
{
	t_ivec2		start;
	t_player	*player;

	player = get_player();
	start = ivec2(20, get_settings()->win_h / 2 - 100);
	put_text(start, WHITE, "Ray angle ");
	print_float(get_math()->base_angle,
		ivec2(start.x + str_px_size("Ray angle "), start.y), WHITE);
	start.y += 20;
	put_text(ivec2(start.x, start.y), WHITE, "Ray increment ");
	print_vec(player->plane_inc,
		ivec2(start.x + str_px_size("Plane increment "), start.y), WHITE);
	start.y += 20;
	put_text(ivec2(start.x, start.y), WHITE, "Direction ");
	print_float(player->direction,
		ivec2(start.x + str_px_size("Direction "), start.y), WHITE);
	start.y += 20;
	put_text(ivec2(start.x, start.y), WHITE, "World pos ");
	print_vec(player->world_pos,
		ivec2(start.x + str_px_size("World pos "), start.y), WHITE);
	start.y += 20;
	put_text(ivec2(start.x, start.y), WHITE, "Grid pos ");
	print_vec(player->cell_pos,
		ivec2(start.x + str_px_size("Grid pos "), start.y), WHITE);
	start.y += 20;
	put_text(ivec2(start.x, start.y), WHITE, "Map pos ");
	print_ivec(player->map_pos,
		ivec2(start.x + str_px_size("Map pos "), start.y), WHITE);
	start.y += 40;
	put_text(ivec2(start.x, start.y), WHITE, "Settings");
	start.y += 20;
	put_text(ivec2(start.x, start.y), WHITE, "FOV ");
	print_int(get_settings()->fov,
		ivec2(start.x + str_px_size("FOV "), start.y), WHITE);
}
