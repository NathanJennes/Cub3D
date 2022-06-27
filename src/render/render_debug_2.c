/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:52:34 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/27 16:15:56 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "colors.h"
#include "core.h"
#include "ui.h"
#include "render.h"

void	debug_light(const t_mlx *app, const t_player *player)
{
	int64_t	i;
	t_light	*l;
	t_ivec3	light;
	t_rgb	color;

	i = 0;
	light = get_lighting_level(vec3(
				(double) get_mouse_pos().x,
				(double) get_mouse_pos().y, 0),
			vec3(player->forward.x, player->forward.y, 0.0));
	while (i < app->gamestate.light_count)
	{
		l = &app->gamestate.lights[i];
		draw_circle(ivec2((int64_t)l->pos.x, (int64_t)l->pos.y), 7,
			(int)l->color.color);
		i++;
	}
	color.color = trgb(0, (int)light.x, (int)light.y, (int)light.z);
	draw_circle(get_mouse_pos(), 10, (int)color.color);
}

void	debug_sprite(const t_mlx *app)
{
	t_sprite	*sprite;

	sprite = &app->sprite_manager.sprites[0];
	if (sprite)
	{
		render_sprite(sprite);
		draw_rect(ivec2((int64_t)sprite->pos.x - sprite->size.x / 2,
				(int64_t)sprite->pos.y - sprite->size.y / 2), ivec2(10, 10),
			trgb(0, 100, 255, 100));
	}
}

static t_vec2	rotate_vector(t_vec2 v, double angle)
{
	t_vec2	new_vector;

	new_vector.x = v.x * cos(angle) - v.y * sin(angle);
	new_vector.y = v.x * sin(angle) + v.y * cos(angle);
	return (new_vector);
}

void	print_player_vector(t_vec2 player_pos)
{
	t_vec2	forward;
	t_vec2	right;
	t_vec2	fov_left;
	t_vec2	fov_right;

	forward = get_player()->forward;
	right = get_player()->right;
	draw_line(v2_to_iv2(player_pos),
		ivec2((int64_t)(player_pos.x + forward.x * CELL_SIZE),
			(int64_t)(player_pos.y + forward.y * CELL_SIZE)), YELLOW);
	draw_line(v2_to_iv2(player_pos),
		ivec2((int64_t)(player_pos.x + right.x * CELL_SIZE),
			(int64_t)(player_pos.y + right.y * CELL_SIZE)), BLUE);
	draw_line(v2_to_iv2(player_pos),
		ivec2((int64_t)(player_pos.x - right.x * CELL_SIZE),
			(int64_t)(player_pos.y - right.y * CELL_SIZE)), GREEN);
	fov_left = rotate_vector(forward, get_math()->r_half_fov);
	fov_right = rotate_vector(forward, -get_math()->r_half_fov);
	draw_line(v2_to_iv2(player_pos),
		ivec2((int64_t)(player_pos.x + fov_left.x * CELL_SIZE),
			(int64_t)(player_pos.y + fov_left.y * CELL_SIZE)), PINK);
	draw_line(v2_to_iv2(player_pos),
		ivec2((int64_t)(player_pos.x + fov_right.x * CELL_SIZE),
			(int64_t)(player_pos.y + fov_right.y * CELL_SIZE)), PINK);
}
