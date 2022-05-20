/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:21:01 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/20 11:41:52 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "ui.h"
#include "render.h"
#include <math.h>

static t_vec2	rotate_vector(t_vec2 v, float angle);
static void		print_player_vector(void);
static void		debug_rays(int fov);

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
	render_circle(v2_to_iv2(get_player()->pos), 10, YELLOW);
	print_player_vector();
	debug_rays(60);
}

static void	debug_rays(int fov)
{
	float		ray_angle;
	float		ray_angle_base;
	float		dist;
	int64_t		i;
	t_vec2		pos;
	t_ivec2		map_pos;
	t_vec2		line_end;

	ray_angle = ((float)fov * (PI / 180.0f)) / (float)WIN_W;
	ray_angle_base = get_player()->direction + ((float)fov / 360.0f);
	while (ray_angle_base < 0.0f)
		ray_angle_base += 2.0f * PI;

	pos = get_player()->pos;
	vec2_divf(&pos, CELL_WIDTH);
	map_pos.x = (int)pos.x;
	map_pos.y = (int)pos.y;
	i = 0;
	t_vec2 ray = vec2(cosf(ray_angle_base), sinf(ray_angle_base));
	ft_print_vec2(ray);
	while (i < WIN_W)
	{
		ray = vec2(cosf(ray_angle_base), sinf(ray_angle_base));
		dist = shoot_ray(ray, pos, map_pos);
//		dist *= (float)cos(ray_angle_base);
		ray_angle_base += ray_angle;
		i++;
	}
}

void	print_player_vector(void)
{
	t_vec2	player_pos;
	t_vec2	forward;
	t_vec2	right;

	player_pos = get_player()->pos;
	forward = get_player()->forward;
	right = get_player()->right;
//	ft_print_vec2(right);
	render_line(v2_to_iv2(player_pos),
			ivec2(player_pos.x + forward.x * CELL_WIDTH,
					player_pos.y + forward.y * CELL_WIDTH), BLACK, BLACK);
	render_line(v2_to_iv2(player_pos),
			ivec2(player_pos.x + right.x * CELL_WIDTH,
					player_pos.y + right.y * CELL_WIDTH), BLUE, BLUE);
	render_line(v2_to_iv2(player_pos),
			ivec2(player_pos.x - right.x * CELL_WIDTH,
					player_pos.y - right.y * CELL_WIDTH), GREEN, GREEN);
}

static t_vec2	rotate_vector(t_vec2 v, float angle)
{
	t_vec2	new_vector;

	new_vector.x = v.x * cos(angle) - v.y * sin(angle);
	new_vector.y = v.x * -sin(angle) + v.y * cos(angle);
	return (new_vector);
}
