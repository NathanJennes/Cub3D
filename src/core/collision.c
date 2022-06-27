/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:23:14 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/16 13:23:54 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "render.h"

static void	check_xpos(t_vec2 direction, t_vec2 future_pos);
static void	check_ypos(t_vec2 direction, t_vec2 future_pos);

void	is_colliding(t_vec2 future_pos)
{
	t_player	*player;
	t_vec2		direction;

	player = get_player();
	direction = vec2(future_pos.x - player->world_pos.x,
			future_pos.y - player->world_pos.y);
	vec2_normalize(&direction);
	check_xpos(direction, future_pos);
	check_ypos(direction, future_pos);
}

static void	check_xpos(t_vec2 direction, t_vec2 future_pos)
{
	t_ivec2		dx;
	t_player	*player;

	player = get_player();
	if (direction.x > 0)
	{
		dx = ivec2((int64_t)(future_pos.x + COLLISION_PAD),
				(int64_t)player->world_pos.y);
		if (get_map_type(dx.x / CELL_SIZE, dx.y / CELL_SIZE) == EMPTY)
			player->world_pos.x = future_pos.x;
	}
	else if (direction.x < 0)
	{
		dx = ivec2((int64_t)(future_pos.x - COLLISION_PAD),
				(int64_t)player->world_pos.y);
		if (get_map_type(dx.x / CELL_SIZE, dx.y / CELL_SIZE) == EMPTY)
			player->world_pos.x = future_pos.x;
	}
}

static void	check_ypos(t_vec2 direction, t_vec2 future_pos)
{
	t_ivec2		dy;
	t_player	*player;

	player = get_player();
	if (direction.y > 0)
	{
		dy = ivec2((int64_t)player->world_pos.x,
				(int64_t)(future_pos.y + COLLISION_PAD));
		if (get_map_type(dy.x / CELL_SIZE, dy.y / CELL_SIZE) == EMPTY)
			player->world_pos.y = future_pos.y;
	}
	else if (direction.y < 0)
	{
		dy = ivec2((int64_t)player->world_pos.x,
				(int64_t)(future_pos.y - COLLISION_PAD));
		if (get_map_type(dy.x / CELL_SIZE, dy.y / CELL_SIZE) == EMPTY)
			player->world_pos.y = future_pos.y;
	}
}
