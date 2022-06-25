/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:09:46 by Cyril             #+#    #+#             */
/*   Updated: 2022/06/25 18:16:10 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "render.h"

inline static void	render_map(const t_map_info *map);

void	render_map_menu(void)
{
	t_mlx	*app;

	app = get_app();
	render_map(get_map_infos());
	draw_circle(v2_to_iv2(get_player()->world_pos), MMAP_PLAYER_DIAM, GREEN);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
}

inline static void	render_map(const t_map_info *map)
{
	int64_t				y;
	int64_t				x;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->map[y][x] == WALL)
				draw_rect(ivec2(x * CELL_SIZE, y * CELL_SIZE), \
					ivec2(CELL_SIZE, CELL_SIZE), DARK_GREY);
			else if (map->map[y][x] == EMPTY)
				draw_rect(ivec2(x * CELL_SIZE, y * CELL_SIZE), \
					ivec2(CELL_SIZE, CELL_SIZE), BLACK);
		}
	}
}
