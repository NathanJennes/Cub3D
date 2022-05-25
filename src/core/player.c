/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:11:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/25 18:00:56 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <math.h>

static void	update_player_forward_vec(t_player *player);
static void	update_player_right_vec(t_player *player);
static void	update_player_cell_pos(t_player *player);
static void	update_player_map_vec(t_player *player);

void	update_player_vectors(t_player *player)
{
	update_player_forward_vec(player);
	update_player_right_vec(player);
	update_player_cell_pos(player);
	update_player_map_vec(player);
	if (get_player()->direction < 0.0f)
		get_player()->direction += (float)(TWO_PI);
	else if (get_player()->direction > TWO_PI)
		get_player()->direction -= (float)(TWO_PI);
	get_player()->ray_increment = \
	((float)get_settings()->fov * (PI / 180.0f)) / (float)WIN_W;
	get_player()->ray_angle = \
	get_player()->direction + ((float)get_settings()->fov / 360.0f) * PI;
	if (get_player()->ray_angle < 0.0f)
		get_player()->ray_angle += (float)(TWO_PI);
	else if (get_player()->ray_angle > TWO_PI)
		get_player()->ray_angle -= (float)(TWO_PI);
}

static void	update_player_forward_vec(t_player *player)
{
	player->forward.x = sinf(player->direction);
	player->forward.y = cosf(player->direction);
}

static void	update_player_right_vec(t_player *player)
{
	player->right.x = cosf(player->direction);
	player->right.y = -sinf(player->direction);
}

static void	update_player_cell_pos(t_player *player)
{
	player->cell_pos = player->world_pos;
	vec2_divf(&player->cell_pos, CELL_HEIGHT);
}

static void	update_player_map_vec(t_player *player)
{
	player->map_pos = v2_to_iv2(player->cell_pos);
}
