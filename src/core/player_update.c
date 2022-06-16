/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:00:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/16 15:43:26 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"
#include "render.h"

static void	update_player_position(t_player *player, t_vec2 future_pos,
				double delta_time);
static void	update_player_direction(t_player *player, double delta_time);

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
	get_player()->direction -= 0.0005 * (get_settings()->cam_sensitivity
		* (double)get_app()->mouse.delta.x);
	if (is_key_down(KEY_RIGHT))
		player->direction -= PI / 4.0 * settings->cam_sensitivity * delta_time;
	if (is_key_down(KEY_LEFT))
		player->direction += PI / 4.0 * settings->cam_sensitivity * delta_time;
}
