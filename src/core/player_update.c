/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:00:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/10 21:01:20 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"
#include "render.h"

static void		is_colliding(t_vec2 future_pos);

void	update_player(t_player *player)
{
	t_vec2		future_pos;
	t_settings	*settings;
	double		delta_time;

	settings = get_settings();
	delta_time = get_app()->delta_time;
	future_pos = get_player()->world_pos;
	if (is_key_down(KEY_RIGHT))
		player->direction -= PI / 4.0 * settings->cam_sensitivity * delta_time;
	if (is_key_down(KEY_LEFT))
		player->direction += PI / 4.0 * settings->cam_sensitivity * delta_time;
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
	update_player_vectors(player);
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
	ray = shoot_ray(direction, player->world_pos, player->map_pos, (max_dist + 5) / CELL_SIZE);
	if (ray.hit == FALSE)
		player->world_pos = future_pos;
	else
	{
		direction = vec2(future_pos.x - player->world_pos.x, player->world_pos.y);
		max_dist = vec2_mag(direction);
		vec2_normalize(&direction);
		ray = shoot_ray(direction, player->world_pos, player->map_pos, (max_dist + 5) / CELL_SIZE);
		if (ray.hit == FALSE)
			player->world_pos.x = future_pos.x;

		direction = vec2(player->world_pos.x, future_pos.y - player->world_pos.y);
		max_dist = vec2_mag(direction);
		vec2_normalize(&direction);
		ray = shoot_ray(direction, player->world_pos, player->map_pos, (max_dist + 5) / CELL_SIZE);
		if (ray.hit == FALSE)
			player->world_pos.y = future_pos.y;
	}
	ft_print_vec2(player->world_pos);
}
