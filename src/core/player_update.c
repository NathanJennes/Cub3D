/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:00:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/29 17:25:08 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"
#include "render.h"

inline static void	update_player_position(t_player *player, t_vec2 future_pos,
						double shift);
inline static void	clamp_player_direction(t_player *player,
						const t_settings *settings);

void	update_player(t_player *player, t_bool handle_input)
{
	t_vec2	future_pos;
	double	shift;

	shift = 1.0;
	if (is_key_down(KEY_LSHIFT))
		shift = 2.0;
	future_pos = get_player()->world_pos;
	update_player_position(player, future_pos, shift);
	update_player_direction(player, handle_input);
	update_player_vectors(player);
}

inline static void	update_player_position(t_player *player, t_vec2 future_pos,
		double shift)
{
	if (is_key_down(KEY_D))
	{
		future_pos.y += PLAYER_SPEED * player->right.y * shift * 0.01;
		future_pos.x += PLAYER_SPEED * player->right.x * shift * 0.01;
	}
	if (is_key_down(KEY_A))
	{
		future_pos.y -= PLAYER_SPEED * player->right.y * shift * 0.01;
		future_pos.x -= PLAYER_SPEED * player->right.x * shift * 0.01;
	}
	if (is_key_down(KEY_W))
	{
		future_pos.y += PLAYER_SPEED * player->forward.y * shift * 0.01;
		future_pos.x += PLAYER_SPEED * player->forward.x * shift * 0.01;
	}
	if (is_key_down(KEY_S))
	{
		future_pos.y -= PLAYER_SPEED * player->forward.y * shift * 0.01;
		future_pos.x -= PLAYER_SPEED * player->forward.x * shift * 0.01;
	}
	is_colliding(future_pos);
}

void	update_player_direction(t_player *player, t_bool handle_input)
{
	t_settings	*settings;

	settings = get_settings();
	if (handle_input)
	{
		get_app()->mouse.delta.x = \
			get_mouse_pos().x - get_app()->settings.halfw_w;
		get_player()->direction -= 0.002 * (get_settings()->cam_sensitivity
			* (double)get_app()->mouse.delta.x);
		if (is_key_down(KEY_RIGHT))
			player->direction -= \
				PI / 40.0 * settings->cam_sensitivity;
		if (is_key_down(KEY_LEFT))
			player->direction += \
				PI / 40.0 * settings->cam_sensitivity;
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
