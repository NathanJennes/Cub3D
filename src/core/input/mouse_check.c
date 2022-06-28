/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cyril <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:42:37 by Cyril             #+#    #+#             */
/*   Updated: 2022/06/28 21:24:10 by Cyril            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	is_light_inside_map(t_ivec2 mouse_pos)
{
	int64_t		x;
	int64_t		y;
	t_map_info	*map;

	map = get_map_infos();
	x = mouse_pos.x / CELL_SIZE;
	y = mouse_pos.y / CELL_SIZE;
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (map->map[y][x] != EMPTY)
		return (0);
	return (1);
}
