/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:00:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/14 10:25:13 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"
#include "render.h"

static void	update_player_position(t_player *player, t_vec2 future_pos,
				double delta_time);
static void	update_player_direction(t_player *player, double delta_time);
static void	is_colliding(t_vec2 future_pos);

void	update_player(t_player *player)
{
	t_vec2		future_pos;
	double		delta_time;

	delta_time = get_app()->delta_time;
	future_pos = get_player()->world_pos;
	update_player_position(player, future_pos, delta_time);
	update_player_direction(player, delta_time);
	update_player_vectors(player);
}

static void	update_player_position(t_player *player, t_vec2 future_pos,
		double delta_time)
{
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
}

static void	update_player_direction(t_player *player, double delta_time)
{
	t_settings	*settings;

	settings = get_settings();
	get_app()->mouse.delta.x = \
		get_mouse_position().x - get_app()->settings.halfw_w;
	get_player()->direction -= 0.0025 * (get_settings()->cam_sensitivity
		* (double)get_app()->mouse.delta.x);
	if (is_key_down(KEY_RIGHT))
		player->direction -= PI / 4.0 * settings->cam_sensitivity * delta_time;
	if (is_key_down(KEY_LEFT))
		player->direction += PI / 4.0 * settings->cam_sensitivity * delta_time;
}

static void	is_colliding(t_vec2 future_pos)
{
	double		max_dist;
	t_player	*player;
	t_ray		ray;
	t_vec2		direction;

	player = get_player();
	direction = vec2(future_pos.x - player->world_pos.x,
			future_pos.y - player->world_pos.y);
	max_dist = vec2_mag(direction);
	vec2_normalize(&direction);
	ray = shoot_ray(direction, player->world_pos, player->map_pos,
			(max_dist + COLLISION_PAD) / CELL_SIZE);
	if (ray.hit == EMPTY)
	{
		player->world_pos = future_pos;
	}
	else
	{
		direction = \
			vec2(future_pos.x - player->world_pos.x, player->world_pos.y);
		max_dist = vec2_mag(direction);
		vec2_normalize(&direction);
		ray = shoot_ray(direction, player->world_pos, player->map_pos,
				(max_dist + COLLISION_PAD) / CELL_SIZE);
		if (ray.hit == FALSE)
			player->world_pos.x = future_pos.x;
		direction = \
			vec2(player->world_pos.x, future_pos.y - player->world_pos.y);
		max_dist = vec2_mag(direction);
		vec2_normalize(&direction);
		ray = shoot_ray(direction, player->world_pos, player->map_pos,
				(max_dist + COLLISION_PAD) / CELL_SIZE);
		if (ray.hit == FALSE)
			player->world_pos.y = future_pos.y;
	}
}
