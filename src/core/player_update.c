/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:00:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/09 20:09:54 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "bool.h"
#include "input_code.h"
#include <math.h>
#include "render.h"

static t_bool	test_collision(t_vec2 future_pos, t_ivec2 cell);
static void		is_colliding(t_vec2 future_pos);

void	update_player(t_player *player)
{
	t_vec2		future_pos;
	t_settings	*settings;
	double		delta_time;

	settings = get_settings();
	delta_time = get_app()->delta_time;
	future_pos = get_player()->world_pos;
	if (is_key_down(KEY_W))
	{
		future_pos.y += PLAYER_SPEED * player->forward.y * delta_time;
		future_pos.x += PLAYER_SPEED * player->forward.x * delta_time;
		is_colliding(future_pos);
	}
	if (is_key_down(KEY_S))
	{
		future_pos.y -= PLAYER_SPEED * player->forward.y * delta_time;
		future_pos.x -= PLAYER_SPEED * player->forward.x * delta_time;
		is_colliding(future_pos);
	}
	if (is_key_down(KEY_D))
	{
		future_pos.y += PLAYER_SPEED * player->right.y * delta_time;
		future_pos.x += PLAYER_SPEED * player->right.x * delta_time;
		is_colliding(future_pos);
	}
	if (is_key_down(KEY_A))
	{
		future_pos.y -= PLAYER_SPEED * player->right.y * delta_time;
		future_pos.x -= PLAYER_SPEED * player->right.x * delta_time;
		is_colliding(future_pos);
	}
	if (is_key_down(KEY_RIGHT))
		player->direction -= PI / 4.0 * settings->cam_sensitivity * delta_time;
	if (is_key_down(KEY_LEFT))
		player->direction += PI / 4.0 * settings->cam_sensitivity * delta_time;
	update_player_vectors(player);
}

static void	is_colliding(t_vec2 future_pos)
{
	t_vec2		offset_pos;
	t_vec2		cell;
	t_player	*player;

	player = get_player();
	cell = vec2(future_pos.x - player->world_pos.x, future_pos.y - player->world_pos.y);
	ft_print_vec2(cell);
	if (cell.x > 0)
		offset_pos.x = future_pos.x + 5;
	else
		offset_pos.x = future_pos.x - 5;
	if (cell.y > 0)
		offset_pos.y = future_pos.y + 5;
	else
		offset_pos.y = future_pos.y - 5;
	if (get_map_infos()->map[player->map_pos.y][(int)(offset_pos.x / CELL_SIZE)] == EMPTY)
		get_player()->world_pos.x = future_pos.x;
	if (get_map_infos()->map[(int)(offset_pos.y / CELL_SIZE)][player->map_pos.x] == EMPTY)
		get_player()->world_pos.y = future_pos.y;
}

static t_bool	test_collision(t_vec2 future_pos, t_ivec2 cell)
{
	double	corner_dist;
	t_vec2	dist;

	if (get_map_infos()->map[cell.y][cell.x] == 0)
		return (FALSE);
	dist = vec2(fabs(future_pos.x - (double)(cell.x * CELL_SIZE + HALF_CELL)),
			fabs(future_pos.y - (double)(cell.y * CELL_SIZE + HALF_CELL)));
	if (dist.x > MAX_DIST)
		return (FALSE);
	if (dist.y > MAX_DIST)
		return (FALSE);
	if (dist.x <= HALF_CELL)
		return (TRUE);
	if (dist.y <= HALF_CELL)
		return (TRUE);
	corner_dist = sqrt(dist.x - HALF_CELL) + sqrt(dist.y - HALF_CELL);
	return (corner_dist <= SQRT_R);
}
