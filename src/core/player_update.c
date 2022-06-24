/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:00:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/23 14:29:35 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"
#include "render.h"

inline static void	update_player_position(t_player *player, t_vec2 future_pos,
					double delta_time);

void	update_player(t_player *player, t_bool handle_input)
{
	t_vec2		future_pos;
	double		delta_time;

	delta_time = get_app()->delta_time;
	future_pos = get_player()->world_pos;
	update_player_position(player, future_pos, delta_time);
	update_player_direction(player, delta_time, handle_input);
	update_player_vectors(player);
}

inline static void	update_player_position(t_player *player, t_vec2 future_pos,
		double delta_time)
{
	if (is_key_down(KEY_D))
	{
		future_pos.y += PLAYER_SPEED * player->right.y * delta_time;
		future_pos.x += PLAYER_SPEED * player->right.x * delta_time;
	}
	if (is_key_down(KEY_A))
	{
		future_pos.y -= PLAYER_SPEED * player->right.y * delta_time;
		future_pos.x -= PLAYER_SPEED * player->right.x * delta_time;
	}
	if (is_key_down(KEY_W))
	{
		future_pos.y += PLAYER_SPEED * player->forward.y * delta_time;
		future_pos.x += PLAYER_SPEED * player->forward.x * delta_time;
	}
	if (is_key_down(KEY_S))
	{
		future_pos.y -= PLAYER_SPEED * player->forward.y * delta_time;
		future_pos.x -= PLAYER_SPEED * player->forward.x * delta_time;
	}
	is_colliding(future_pos);
}

void	update_player_direction(t_player *player, double delta_time, t_bool handle_input)
{
	t_settings	*settings;

	settings = get_settings();
	if (handle_input)
	{
		get_app()->mouse.delta.x = \
		get_mouse_position().x - get_app()->settings.halfw_w;
		get_player()->direction -= 0.0005 * (get_settings()->cam_sensitivity
											* (double)get_app()->mouse.delta.x);
		if (is_key_down(KEY_RIGHT))
			player->direction -= PI / 4.0 * settings->cam_sensitivity * delta_time;
		if (is_key_down(KEY_LEFT))
			player->direction += PI / 4.0 * settings->cam_sensitivity * delta_time;
	}
	if (player->direction < 0.0)
		player->direction += TWO_PI;
	else if (player->direction > TWO_PI)
		player->direction -= TWO_PI;
	get_math()->base_angle = player->direction + get_math()->r_half_fov;
	if (get_math()->base_angle < 0.0)
		get_math()->base_angle += TWO_PI;
	else if (get_math()->base_angle > TWO_PI)
		get_math()->base_angle -= TWO_PI;
	player->plane_inc = \
			vec2((player->right.x * get_math()->plane_len) / settings->halfw_w,
		(player->right.y * get_math()->plane_len) / settings->halfw_w);
}
