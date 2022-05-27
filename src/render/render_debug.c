/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:21:01 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/27 16:10:31 by njennes          ###   ########.fr       */
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

	for (int64_t i = 0; i < app->gamestate.light_count; i++)
	{
		t_light *l = &app->gamestate.lights[i];
		int col = trgb(0, l->color.x, l->color.y, l->color.z);
		draw_circle(ivec2(l->pos.x, l->pos.y), 7, col);
	}

	draw_circle(v2_to_iv2(get_player()->world_pos), 7, BLACK);
	print_player_vector();
	t_ivec2 mouse_pos = cub_get_mouse_position();
	t_player *player = get_player();
	t_ivec3 light = get_lighting_level(vec3(mouse_pos.x, mouse_pos.y, 0),
		vec3(player->forward.x, player->forward.y, 0.0));
	draw_circle(mouse_pos, 10, trgb(0, light.x, light.y, light.z));
	//debug_rays();
}

static void	debug_rays(void)
NOPROF
{
	int64_t		i;
	t_vec2		ray_direction;
	t_player	*player;
	t_vec2		start;
	t_vec2		inc;
	double		plane_len;

	i = 0;
	player = get_player();
	plane_len = tan((double)get_settings()->fov / 2.0);
	start = vec2(player->world_pos.x + player->forward.x - player->right.x * plane_len,
		player->world_pos.y + player->forward.y - player->right.y * plane_len);
	inc = vec2((player->right.x * plane_len) / HALFW_W, (player->right.y * plane_len) / HALFW_W);
	while (i < WIN_W)
	{
		ray_direction = vec2(start.x - player->world_pos.x, start.y - player->world_pos.y);
		vec2_normalize(&ray_direction);
		player->last_ray = shoot_ray(ray_direction, player->world_pos, player->map_pos);
		print_ray(player->last_ray.hit_pos);
		vec2_add(&start, inc);
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
	fov_left = rotate_vector(forward, get_math()->r_halffov);
	fov_right = rotate_vector(forward, -get_math()->r_halffov);
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
