/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:21:01 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/26 13:40:53 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "colors.h"
#include "core.h"
#include "ui.h"
#include "render.h"

static void		print_ray(t_vec2 hit_pos) NOPROF;
static t_vec2	rotate_vector(t_vec2 v, double angle) NOPROF;
static void		print_player_vector(void) NOPROF;
static void		debug_rays(void) NOPROF;

void	render_test_scene(const t_mlx *app)
{
	int					color;
	const t_map_info	*map = &app->gamestate.map;

	for (int64_t i = 0; i < map->height; i++)
	{
		for (int64_t j = 0; j < map->width; j++)
		{
			if (map->map[i][j] == WALL)
				color = trgb(0, 51, 51, 51);
			else if (map->map[i][j] == EMPTY)
				color = trgb(0, 200, 200, 200);
			else
				color = trgb(0, 0, 0, 0);
			draw_rect(ivec2(j * CELL_WIDTH, i * CELL_WIDTH),
				ivec2(CELL_WIDTH, CELL_WIDTH), color);
		}
	}
	draw_circle(v2_to_iv2(get_player()->world_pos), 7, BLACK);
	print_player_vector();
	debug_rays();
}

static void	debug_rays(void)
NOPROF
{
	double		offset;
	int64_t		i;
	t_vec2		ray_direction;
	t_player	*player;
	double		half_width;

	i = 0;
	half_width = tan(get_settings()->fov * PI / 360.0f);
	player = get_player();
	while (i < WIN_W)
	{
		offset = (((double)i * 2.0f / (WIN_W - 1.0f)) - 1.0f) * half_width;
		ray_direction.x = player->forward.x - offset * player->right.x;
		ray_direction.y = player->forward.y - offset * player->right.y;
		player->last_ray = shoot_ray(ray_direction, player->map_pos);
		print_ray(player->last_ray.hit_pos);
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
		ivec2(player_pos.x + forward.x * CELL_WIDTH,
			player_pos.y + forward.y * CELL_WIDTH), BLACK);
	draw_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x + right.x * CELL_WIDTH,
			player_pos.y + right.y * CELL_WIDTH), BLUE);
	draw_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x - right.x * CELL_WIDTH,
			player_pos.y - right.y * CELL_WIDTH), GREEN);
	fov_left = rotate_vector(forward, ((double)get_settings()->fov / 360.0f) * PI);
	fov_right = rotate_vector(forward, -((double)get_settings()->fov / 360.0f) * PI);
	draw_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x + fov_left.x * CELL_WIDTH,
			player_pos.y + fov_left.y * CELL_WIDTH), PINK);
	draw_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x + fov_right.x * CELL_WIDTH,
			player_pos.y + fov_right.y * CELL_WIDTH), PINK);
}

static t_vec2	rotate_vector(t_vec2 v, double angle)
NOPROF
{
	t_vec2	new_vector;

	new_vector.x = v.x * cos(angle) - v.y * sin(angle);
	new_vector.y = v.x * sin(angle) + v.y * cos(angle);
	return (new_vector);
}
