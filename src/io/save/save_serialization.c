/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_serialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:22:14 by njennes           #+#    #+#             */
/*   Updated: 2022/06/17 14:59:35 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

inline static void	serialize_player(int fd, t_player player);
inline static void	serialize_map(int fd, t_map_info map);
inline static void	serialize_map_walls(int fd, t_map_info map);

void	serialize_game(int fd)
{
	t_mlx		*app;
	t_gamestate	*game;

	app = get_app();
	game = &app->gamestate;
	dprintf(fd, "CUB_SAVE\n");
	serialize_player(fd, game->player);
	serialize_map(fd, game->map);
}

inline static void	serialize_player(int fd, t_player player)
{
	dprintf(fd, "PLAYER_START\n");
	dprintf(fd, "POS %d %d %d\n",
		(int)player.world_pos.x,
		(int)player.world_pos.y,
		(int)player.direction);
	dprintf(fd, "PLAYER_END\n");
}

inline static void	serialize_map(int fd, t_map_info map)
{
	dprintf(fd, "MAP_START\n");
	dprintf(fd, "W %d\n", (int)map.width);
	dprintf(fd, "H %d\n", (int)map.height);
	dprintf(fd, "SPAWN %d %d %c\n",
		(int)map.spawn_pos.x, (int)map.spawn_pos.y, (char)map.spawn_dir);
	dprintf(fd, "CEILING %d %d %d\n",
		(int)map.ceiling.r, (int)map.ceiling.g,
		(int)map.ceiling.b);
	dprintf(fd, "FLOOR %d %d %d\n",
		(int)map.floor.r, (int)map.floor.g,
		(int)map.floor.b);
	dprintf(fd, "NO_TEX %s\n", get_texture_from_id(map.tx_list[NORTH])->name);
	dprintf(fd, "EA_TEX %s\n", get_texture_from_id(map.tx_list[EAST])->name);
	dprintf(fd, "SO_TEX %s\n", get_texture_from_id(map.tx_list[SOUTH])->name);
	dprintf(fd, "WE_TEX %s\n", get_texture_from_id(map.tx_list[WEST])->name);
	serialize_map_walls(fd, map);
	dprintf(fd, "MAP_END\n");
}

inline static void	serialize_map_walls(int fd, t_map_info map)
{
	int64_t	i;
	int64_t	j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (map.map[i][j] == WALL)
				dprintf(fd, "%d", 1);
			else if (map.map[i][j] == EMPTY)
				dprintf(fd, "%d", 0);
			else if (map.map[i][j] == VOID)
				dprintf(fd, " ");
			j++;
		}
		dprintf(fd, "\n");
		i++;
	}
}
