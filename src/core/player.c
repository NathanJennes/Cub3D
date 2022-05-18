/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:11:13 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/18 18:37:53 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <math.h>

void	update_player_forward_vec(t_player *player)
{
	player->forward = vec2(sin(player->direction),
			cos(player->direction));
}

void	update_player_right_vec(t_player *player)
{
	player->right = vec2(cos(player->direction),
			-sin(player->direction));
}
