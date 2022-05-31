/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:00:21 by njennes           #+#    #+#             */
/*   Updated: 2022/05/27 13:51:45 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "input_code.h"

void	update_player(t_player *player)
{
	if (is_key_down(KEY_W))
	{
		player->world_pos.y += PLAYER_SPEED * get_player()->forward.y;
		player->world_pos.x += PLAYER_SPEED * get_player()->forward.x;
	}
	if (is_key_down(KEY_S))
	{
		player->world_pos.y -= PLAYER_SPEED * get_player()->forward.y;
		player->world_pos.x -= PLAYER_SPEED * get_player()->forward.x;
	}
	if (is_key_down(KEY_D))
	{
		player->world_pos.y += PLAYER_SPEED * get_player()->right.y;
		player->world_pos.x += PLAYER_SPEED * get_player()->right.x;
	}
	if (is_key_down(KEY_A))
	{
		player->world_pos.y -= PLAYER_SPEED * get_player()->right.y;
		player->world_pos.x -= PLAYER_SPEED * get_player()->right.x;
	}
	if (is_key_down(KEY_RIGHT))
		get_player()->direction -= PI / 100.0f;
	if (is_key_down(KEY_LEFT))
		get_player()->direction += PI / 100.0f;
	update_player_vectors(get_player());
}
