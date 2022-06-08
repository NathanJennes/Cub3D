/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:00:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/09 00:39:24 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "bool.h"
#include "input_code.h"
#include <math.h>
#include "render.h"

static int64_t	get_nearest_cell(int64_t value);
static t_bool	is_colliding(t_vec2 player, t_ivec2 wall);

// TODO: make forward only 0, 1 or -1 or make function how gets nearest square in player direction.
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
		future_pos.y += PLAYER_SPEED * get_player()->forward.y * delta_time;
		future_pos.x += PLAYER_SPEED * get_player()->forward.x * delta_time;
		get_player()->wall_pos.x = \
			get_nearest_cell((get_player()->map_pos.x + get_player()->forward.x) * CELL_SIZE);
		get_player()->wall_pos.y = \
			get_nearest_cell((get_player()->map_pos.y + get_player()->forward.y) * CELL_SIZE);
		if (!is_colliding(future_pos, get_player()->wall_pos))
			get_player()->world_pos = future_pos;
	}
	if (is_key_down(KEY_S))
	{
		future_pos.y -= PLAYER_SPEED * get_player()->forward.y * delta_time;
		future_pos.x -= PLAYER_SPEED * get_player()->forward.x * delta_time;
		get_player()->wall_pos.x = \
			get_nearest_cell((get_player()->map_pos.x - get_player()->forward.x) * CELL_SIZE);
		get_player()->wall_pos.y = \
			get_nearest_cell((get_player()->map_pos.y - get_player()->forward.y) * CELL_SIZE);
		if (!is_colliding(future_pos, get_player()->wall_pos))
			get_player()->world_pos = future_pos;
	}
	if (is_key_down(KEY_D))
	{
		future_pos.y += PLAYER_SPEED * get_player()->right.y * delta_time;
		future_pos.x += PLAYER_SPEED * get_player()->right.x * delta_time;
		get_player()->wall_pos.x = \
			get_nearest_cell((get_player()->map_pos.x + get_player()->right.x) * CELL_SIZE);
		get_player()->wall_pos.y = \
			get_nearest_cell((get_player()->map_pos.y + get_player()->right.y) * CELL_SIZE);
		if (!is_colliding(future_pos, get_player()->wall_pos))
			get_player()->world_pos = future_pos;
	}
	if (is_key_down(KEY_A))
	{
		future_pos.y -= PLAYER_SPEED * get_player()->right.y * delta_time;
		future_pos.x -= PLAYER_SPEED * get_player()->right.x * delta_time;
		get_player()->wall_pos.x = \
			get_nearest_cell((get_player()->map_pos.x - get_player()->right.x) * CELL_SIZE);
		get_player()->wall_pos.y = \
			get_nearest_cell((get_player()->map_pos.y - get_player()->right.y) * CELL_SIZE);
		if (!is_colliding(future_pos, get_player()->wall_pos))
			get_player()->world_pos = future_pos;
	}
	if (is_key_down(KEY_RIGHT))
		get_player()->direction -= PI / 4.0 * settings->cam_sensitivity * delta_time;
	if (is_key_down(KEY_LEFT))
		get_player()->direction += PI / 4.0 * settings->cam_sensitivity * delta_time;
	update_player_vectors(get_player());
}

static t_bool	is_colliding(t_vec2 player, t_ivec2 wall)
{
	double	corner_dist;
	t_vec2	dist;

	if (get_map_infos()->map[wall.y / CELL_SIZE][wall.x / CELL_SIZE] == 0)
		return (FALSE);
	dist = vec2(fabs(player.x - (wall.x + HALF_CELL)),
			fabs(player.y - (wall.y + HALF_CELL)));
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

static int64_t	get_nearest_cell(int64_t value)
{
	int64_t	res;
	int64_t	left;

	left = value % CELL_SIZE;
	if (left == 0)
		return (value);
	printf("%lld -- ", value);
	res = value + CELL_SIZE - left;
	printf("%lld\n", res);
	return (res);
}
