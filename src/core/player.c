/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:11:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/06/13 15:24:47 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <math.h>

inline static void	update_player_forward_vec(t_player *player);
inline static void	update_player_right_vec(t_player *player);
inline static void	update_player_cell_pos(t_player *player);
inline static void	update_player_map_vec(t_player *player);

void	update_player_vectors(t_player *player)
{
	t_settings	*settings;

	settings = get_settings();
	update_player_forward_vec(player);
	update_player_right_vec(player);
	update_player_cell_pos(player);
	update_player_map_vec(player);
}

inline static void	update_player_forward_vec(t_player *player)
{
	player->forward.x = sin(player->direction);
	player->forward.y = cos(player->direction);
}

inline static void	update_player_right_vec(t_player *player)
{
	player->right.x = -cos(player->direction);
	player->right.y = sin(player->direction);
}

inline static void	update_player_cell_pos(t_player *player)
{
	player->cell_pos = player->world_pos;
	vec2_divf(&player->cell_pos, CELL_SIZE);
}

inline static void	update_player_map_vec(t_player *player)
{
	player->map_pos = v2_to_iv2(player->cell_pos);
}
