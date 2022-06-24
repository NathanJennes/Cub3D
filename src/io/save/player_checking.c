/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:31:18 by njennes           #+#    #+#             */
/*   Updated: 2022/06/23 18:36:51 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "core.h"

t_bool	is_player_position_legal(t_gamestate *gamestate)
{
	t_player	*player;

	player = &gamestate->player;
	if (player->world_pos.x < 0 || player->world_pos.y < 0)
		return (FALSE);
	if (player->world_pos.x > (double)gamestate->map.width * CELL_SIZE
		|| player->world_pos.y > (double)gamestate->map.height * CELL_SIZE)
		return (FALSE);
	if (gamestate->map.map[player->map_pos.y][player->map_pos.x] != EMPTY)
		return (FALSE);
	return (TRUE);
}
