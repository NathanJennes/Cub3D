/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:21:01 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/26 12:57:24 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "core.h"
#include "ui.h"
#include "render.h"

inline static void		print_ray(t_vec2 hit_pos);
inline static void		debug_rays(t_player *player);
inline static void		debug_minimap(const t_map_info *map);
void				print_player_vector(t_vec2 player_pos);
void				debug_sprite(const t_mlx *app);
void				debug_light(const t_mlx *app, const t_player *player);

void	render_debug(t_mlx *app)
{
	t_player			*player;

	if (app->ui.debug_state == NO_DEBUG)
		return ;
	player = get_player();
	if (app->ui.debug_state >= LVL1)
		debug_minimap(&app->gamestate.map);
	if (app->ui.debug_state == LVL2)
		debug_rays(player);
	if (app->ui.debug_state == LVL3)
		debug_light(app, player);
	print_player_vector(player->world_pos);
	debug_sprite(app);
}

inline static void	debug_minimap(const t_map_info *map)
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
			draw_line(ivec2(x * CELL_SIZE, y * CELL_SIZE),
				ivec2(x * CELL_SIZE, (y + 1) * CELL_SIZE), GREY);
			draw_line(ivec2(x * CELL_SIZE, y * CELL_SIZE),
				ivec2((x + 1) * CELL_SIZE, y * CELL_SIZE), GREY);
		}
	}
	draw_line(ivec2(0 * CELL_SIZE, y * CELL_SIZE),
		ivec2(x * CELL_SIZE, y * CELL_SIZE), GREY);
	draw_line(ivec2(x * CELL_SIZE, 0 * CELL_SIZE),
		ivec2(x * CELL_SIZE, y * CELL_SIZE), GREY);
}

inline static void	debug_rays(t_player *player)
{
	int64_t		i;
	t_vec2		ray_direction;
	t_vec2		start;
	t_settings	*settings;
	t_ray		ray;

	i = 0;
	settings = get_settings();
	player = get_player();
	start = vec2(player->world_pos.x + player->forward.x
			- player->right.x * get_math()->plane_len,
			player->world_pos.y + player->forward.y
			- player->right.y * get_math()->plane_len);
	while (i < settings->win_w)
	{
		ray_direction = vec2(start.x - player->world_pos.x,
				start.y - player->world_pos.y);
		vec2_normalize(&ray_direction);
		ray = shoot_ray(ray_direction, player->world_pos,
				player->map_pos, RAY_LENGTH);
		print_ray(ray.hit_pos);
		vec2_add(&start, player->plane_inc);
		i++;
	}
}

inline static void	print_ray(t_vec2 hit_pos)
{
	if (get_ui()->debug_state == LVL2)
	{
		draw_line(v2_to_iv2(get_player()->world_pos), v2_to_iv2(hit_pos), RED);
		draw_circle(v2_to_iv2(hit_pos), 10, YELLOW);
	}
}
