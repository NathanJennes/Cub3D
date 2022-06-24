/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:21:01 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/24 10:31:23 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "colors.h"
#include "core.h"
#include "ui.h"
#include "render.h"

inline static void		print_ray(t_vec2 hit_pos) NOPROF;
inline static void		debug_rays(void) NOPROF;
inline static t_vec2	rotate_vector(t_vec2 v, double angle) NOPROF;
inline static void		print_player_vector(void) NOPROF;

void	render_debug(t_mlx *app)
{
	int64_t				i;
	int64_t				j;
	int					color;
	t_player			*player = get_player();
	const t_map_info	*map = &app->gamestate.map;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == WALL)
			{
				color = trgb(0, 51, 51, 51);
				draw_rect(ivec2(j * CELL_SIZE, i * CELL_SIZE),
					ivec2(CELL_SIZE, CELL_SIZE), color);
			}
			else if (map->map[i][j] == EMPTY)
			{
				color = trgb(0, 0, 0, 0);
				draw_rect(ivec2(j * CELL_SIZE, i * CELL_SIZE),
					ivec2(CELL_SIZE, CELL_SIZE), color);
			}
			draw_line(ivec2(j * CELL_SIZE, i * CELL_SIZE),
				ivec2(j * CELL_SIZE, (i + 1) * CELL_SIZE), GREY);
			draw_line(ivec2(j * CELL_SIZE, i * CELL_SIZE),
				ivec2((j + 1) * CELL_SIZE, i * CELL_SIZE), GREY);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < app->gamestate.light_count)
	{
		t_light *l = &app->gamestate.lights[i];
		draw_circle(ivec2(l->pos.x, l->pos.y), 7, l->color.color);
		i++;
	}
	t_ivec3 light = get_lighting_level
		(vec3(get_mouse_position().x, get_mouse_position().y, 0),
		vec3(player->forward.x, player->forward.y, 0.0));
	draw_circle(get_mouse_position(), 10, trgb(0, light.x, light.y, light.z));

	if (app->ui.debug == TRUE)
		debug_rays();

	draw_circle(app->debug.dx, 5, BLUE);
	draw_circle(app->debug.dy, 5, BLUE);
	print_player_vector();

	t_sprite	*sprite = &app->sprite_manager.sprites[0];
	if (sprite)
	{
		render_sprite(sprite);
		draw_rect(ivec2(sprite->pos.x - sprite->size.x / 2,
				sprite->pos.y - sprite->size.y / 2), ivec2(10, 10),
			trgb(0, 100, 255, 100));
	}
}

static void	debug_rays(void)
NOPROF
{
	int64_t		i;
	t_vec2		ray_direction;
	t_player	*player;
	t_vec2		start;
	t_settings	*settings;
	t_ray		ray;

	settings = get_settings();
	i = 0;
	player = get_player();
	start = vec2(player->world_pos.x + player->forward.x - player->right.x * get_math()->plane_len,
		player->world_pos.y + player->forward.y - player->right.y * get_math()->plane_len);
	while (i < settings->win_w)
	{
		ray_direction = vec2(start.x - player->world_pos.x, start.y - player->world_pos.y);
		vec2_normalize(&ray_direction);
		ray = shoot_ray(ray_direction, player->world_pos, player->map_pos, RAY_LENGTH);
		print_ray(ray.hit_pos);
		vec2_add(&start, player->plane_inc);
		i++;
	}
}

void	print_ray(t_vec2 hit_pos)
NOPROF
{
	draw_line(v2_to_iv2(get_player()->world_pos), v2_to_iv2(hit_pos), RED);
	draw_circle(v2_to_iv2(hit_pos), 10, YELLOW);
}

void	print_player_vector(void)
NOPROF
{
	t_vec2	player_pos;
	t_vec2	forward;
	t_vec2	right;
	t_vec2	fov_left;
	t_vec2	fov_right;

	player_pos = get_player()->world_pos;
	forward = get_player()->forward;
	right = get_player()->right;
	draw_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x + forward.x * CELL_SIZE,
			player_pos.y + forward.y * CELL_SIZE), YELLOW);
	draw_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x + right.x * CELL_SIZE,
			player_pos.y + right.y * CELL_SIZE), BLUE);
	draw_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x - right.x * CELL_SIZE,
			player_pos.y - right.y * CELL_SIZE), GREEN);
	fov_left = rotate_vector(forward, get_math()->r_half_fov);
	fov_right = rotate_vector(forward, -get_math()->r_half_fov);
	draw_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x + fov_left.x * CELL_SIZE,
			player_pos.y + fov_left.y * CELL_SIZE), PINK);
	draw_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x + fov_right.x * CELL_SIZE,
			player_pos.y + fov_right.y * CELL_SIZE), PINK);
}

inline static t_vec2	rotate_vector(t_vec2 v, double angle)
NOPROF
{
	t_vec2	new_vector;

	new_vector.x = v.x * cos(angle) - v.y * sin(angle);
	new_vector.y = v.x * sin(angle) + v.y * cos(angle);
	return (new_vector);
}
