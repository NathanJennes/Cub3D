/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:00:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/27 14:51:22 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"
#include "render.h"

inline static void	update_player_position(t_player *player, t_vec2 future_pos,
						double delta_time, double shift);
inline static void	clamp_player_direction(t_player *player,
						const t_settings *settings);

void	update_player(t_player *player, t_bool handle_input)
{
	t_vec2	future_pos;
	double	delta_time;
	double	shift;

	shift = 1.0;
	if (is_key_down(KEY_LSHIFT))
		shift = 2.0;
	delta_time = get_app()->delta_time;
	future_pos = get_player()->world_pos;
	update_player_position(player, future_pos, delta_time, shift);
	update_player_direction(player, delta_time, handle_input);
	update_player_vectors(player);
}

inline static void	update_player_position(t_player *player, t_vec2 future_pos,
		double delta_time, double shift)
{
	if (is_key_down(KEY_D))
	{
		future_pos.y += PLAYER_SPEED * player->right.y * delta_time * shift;
		future_pos.x += PLAYER_SPEED * player->right.x * delta_time * shift;
	}
	if (is_key_down(KEY_A))
	{
		future_pos.y -= PLAYER_SPEED * player->right.y * delta_time * shift;
		future_pos.x -= PLAYER_SPEED * player->right.x * delta_time * shift;
	}
	if (is_key_down(KEY_W))
	{
		future_pos.y += PLAYER_SPEED * player->forward.y * delta_time * shift;
		future_pos.x += PLAYER_SPEED * player->forward.x * delta_time * shift;
	}
	if (is_key_down(KEY_S))
	{
		future_pos.y -= PLAYER_SPEED * player->forward.y * delta_time * shift;
		future_pos.x -= PLAYER_SPEED * player->forward.x * delta_time * shift;
	}
	is_colliding(future_pos);
}

void	update_player_direction(t_player *player, double delta_time,
			t_bool handle_input)
{
	t_settings	*settings;

	settings = get_settings();
	if (handle_input)
	{
		get_app()->mouse.delta.x = \
			get_mouse_pos().x - get_app()->settings.halfw_w;
		get_player()->direction -= 0.01 * (get_settings()->cam_sensitivity
			* (double)get_app()->mouse.delta.x) * delta_time;
		if (is_key_down(KEY_RIGHT))
			player->direction -= \
				PI / 4.0 * settings->cam_sensitivity * delta_time;
		if (is_key_down(KEY_LEFT))
			player->direction += \
				PI / 4.0 * settings->cam_sensitivity * delta_time;
	}
	clamp_player_direction(player, settings);
}

inline static void	clamp_player_direction(t_player *player,
			const t_settings *settings)
{
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
