/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:21:01 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/22 18:14:05 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "colors.h"
#include "core.h"
#include "ui.h"
#include "render.h"

static void		print_ray(t_ivec2 hit_pos);
static t_vec2	rotate_vector(t_vec2 v, float angle);
static void		print_player_vector(void);
static void		debug_rays(void);

void	render_test_scene(const t_mlx *app)
{
	int					color;
	const t_map_info	*map = &app->gamestate.map;

	for (int64_t i = 0; i < map->height; i++)
	{
		for (int64_t j = 0; j < map->width; j++)
		{
			if (map->map[i][j] == WALL)
				color = create_trgb(0, 51, 51, 51);
			else if (map->map[i][j] == EMPTY)
				color = create_trgb(0, 200, 200, 200);
			else
				color = create_trgb(0, 0, 0, 0);
			render_rect(ivec2(j * CELL_WIDTH, i * CELL_WIDTH),
				ivec2(CELL_WIDTH, CELL_WIDTH), color);
		}
	}
	render_circle(v2_to_iv2(get_player()->world_pos), 7, BLACK);
	print_player_vector();
	debug_rays();
}

static void	debug_rays(void)
{
	float		start_angle;
	int64_t		i;
	t_vec2		v_ray;
	t_ray		ray;
	t_player	*player;

	i = 0;
	player = get_player();
	start_angle = player->ray_angle;
	while (i < WIN_W)
	{
		v_ray = vec2(sinf(start_angle), cosf(start_angle));
		ray = shoot_ray(v_ray, player->map_pos);
		print_ray(ray.hit_pos);
		start_angle -= player->ray_increment;
		i++;
	}
}

void	print_ray(t_ivec2 hit_pos)
{
	render_line(get_player()->map_pos, hit_pos, RED, RED);
	render_circle(hit_pos, 10, YELLOW);
}

void	print_player_vector(void)
{
	t_vec2	player_pos;
	t_vec2	forward;
	t_vec2	right;
	t_vec2	fov_left;
	t_vec2	fov_right;

	player_pos = get_player()->world_pos;
	forward = get_player()->forward;
	right = get_player()->right;
	render_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x + forward.x * CELL_WIDTH,
			player_pos.y + forward.y * CELL_WIDTH), BLACK, BLACK);
	render_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x + right.x * CELL_WIDTH,
			player_pos.y + right.y * CELL_WIDTH), BLUE, BLUE);
	render_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x - right.x * CELL_WIDTH,
			player_pos.y - right.y * CELL_WIDTH), GREEN, GREEN);
	fov_left = rotate_vector(forward, ((float)get_settings()->fov / 360.0f) * PI);
	fov_right = rotate_vector(forward, -((float)get_settings()->fov / 360.0f) * PI);
	render_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x + fov_left.x * CELL_WIDTH,
			player_pos.y + fov_left.y * CELL_WIDTH), PINK, PINK);
	render_line(v2_to_iv2(player_pos),
		ivec2(player_pos.x + fov_right.x * CELL_WIDTH,
			player_pos.y + fov_right.y * CELL_WIDTH), PINK, PINK);
}

static t_vec2	rotate_vector(t_vec2 v, float angle)
{
	t_vec2	new_vector;

	new_vector.x = v.x * cos(angle) - v.y * sin(angle);
	new_vector.y = v.x * sin(angle) + v.y * cos(angle);
	return (new_vector);
}
