/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:11:29 by njennes           #+#    #+#             */
/*   Updated: 2022/06/15 17:48:58 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"

inline static void	draw_cells(int cell_size, t_vec2 offset);
inline static void	render_mmap_wall(int x, int y, int cell_size);
inline static void	render_mmap_empty(int x, int y, int cell_size);

void	render_minimap(double zoom)
{
	t_player	*player;
	t_mmap		*minimap;
	int64_t		cell_size;
	t_ivec2		player_pos;
	t_vec2		offset;

	player = get_player();
	minimap = &get_ui()->minimap;
	cell_size = MMAP_ZOOM_FACTOR * zoom;
	player_pos.x = minimap->mmap_halfw + MMAP_PAD;
	player_pos.y = minimap->mmap_halfh + MMAP_PAD;
	offset.x = -player->cell_pos.x * cell_size + player_pos.x;
	offset.y = -player->cell_pos.y * cell_size + player_pos.y;
	draw_rect(ivec2(MMAP_PAD / 2, MMAP_PAD / 2),
		ivec2(minimap->mmap_w + MMAP_PAD, minimap->mmap_h + MMAP_PAD),
		BLACK);
	draw_cells(cell_size, offset);
	draw_circle(player_pos, MMAP_PLAYER_DIAM, GREEN);
}

inline static void	draw_cells(int cell_size, t_vec2 offset)
{
	t_map_info	*map;
	int64_t		i;
	int64_t		j;
	int64_t		x_start;
	int64_t		y_start;

	map = get_map_infos();
	x_start = (int64_t)offset.x;
	y_start = (int64_t)offset.y;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == WALL)
				render_mmap_wall(x_start + j * cell_size,
					y_start + i * cell_size, cell_size);
			if (map->map[i][j] == EMPTY)
				render_mmap_empty(x_start + j * cell_size,
					y_start + i * cell_size, cell_size);
			j++;
		}
		i++;
	}
}

inline static void	render_mmap_wall(int x, int y, int cell_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < cell_size)
	{
		j = 0;
		while (j < cell_size)
		{
			if (!outside_mmap_bounds(x + j, y + i))
				set_screen_pixel(x + j, y + i, trgb(0, 150, 150, 150));
			j++;
		}
		i++;
	}
}

inline static void	render_mmap_empty(int x, int y, int cell_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < cell_size)
	{
		j = 0;
		while (j < cell_size)
		{
			if (!outside_mmap_bounds(x + j, y + i))
				set_screen_pixel(x + j, y + i, trgb(0, 250, 250, 250));
			j++;
		}
		i++;
	}
}

int	outside_mmap_bounds(int x, int y)
{
	if (x < MMAP_PAD || x > MMAP_PAD + get_ui()->minimap.mmap_w || y < MMAP_PAD || y > MMAP_PAD
		+ get_ui()->minimap.mmap_h)
		return (1);
	return (0);
}
