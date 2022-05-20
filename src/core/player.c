/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:11:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/20 10:32:57 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <math.h>

void	update_player_forward_vec(t_player *player)
{
	player->forward.x = sinf(player->direction);
	player->forward.y = cosf(player->direction);
}

void	update_player_right_vec(t_player *player)
{
	player->right.x = cosf(player->direction);
	player->right.y = -sinf(player->direction);
}
