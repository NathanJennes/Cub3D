/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:00:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/01 15:21:50 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"

void	update_player(t_player *player)
{
	t_settings	*settings;
	double	delta_time;

	settings = get_settings();
	delta_time = get_app()->delta_time;
	if (is_key_down(KEY_W))
	{
		player->world_pos.y += PLAYER_SPEED * get_player()->forward.y * delta_time;
		player->world_pos.x += PLAYER_SPEED * get_player()->forward.x * delta_time;
	}
	if (is_key_down(KEY_S))
	{
		player->world_pos.y -= PLAYER_SPEED * get_player()->forward.y * delta_time;
		player->world_pos.x -= PLAYER_SPEED * get_player()->forward.x * delta_time;
	}
	if (is_key_down(KEY_D))
	{
		player->world_pos.y += PLAYER_SPEED * get_player()->right.y * delta_time;
		player->world_pos.x += PLAYER_SPEED * get_player()->right.x * delta_time;
	}
	if (is_key_down(KEY_A))
	{
		player->world_pos.y -= PLAYER_SPEED * get_player()->right.y * delta_time;
		player->world_pos.x -= PLAYER_SPEED * get_player()->right.x * delta_time;
	}
	if (is_key_down(KEY_RIGHT))
		get_player()->direction -= PI / 4.0 * settings->cam_sensitivity * delta_time;
	if (is_key_down(KEY_LEFT))
		get_player()->direction += PI / 4.0 * settings->cam_sensitivity * delta_time;
	update_player_vectors(get_player());
}
