/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:22:14 by njennes           #+#    #+#             */
/*   Updated: 2022/05/15 12:29:02 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	serialize_player(int fd, t_player player);
static void	serialize_map(int fd, t_map_info map);
static void	serialize_map_walls(int fd, t_map_info map);

void	serialize_game(int fd)
{
	t_mlx		*app;
	t_gamestate	*game;

	app = get_app();
	game = &app->gamestate;
	serialize_player(fd, game->player);
	serialize_map(fd, game->map);
}

static void	serialize_player(int fd, t_player player)
{
	ft_dprintf(fd, "PLAYER_START\n");
	ft_dprintf(fd, "POS %d %d %d\n",
		(int)player.pos.x, (int)player.pos.y, (int)player.direction);
	ft_dprintf(fd, "PLAYER_END\n");
}

static void	serialize_map(int fd, t_map_info map)
{
	ft_dprintf(fd, "MAP_START\n");
	ft_dprintf(fd, "W %d\n", (int)map.width);
	ft_dprintf(fd, "H %d\n", (int)map.height);
	ft_dprintf(fd, "SPAWN %d %d %c\n",
		(int)map.spawn_pos.x, (int)map.spawn_pos.y, (char)map.spawn_dir);
	ft_dprintf(fd, "CEILING %d %d %d\n",
		(int)map.ceiling_color.x, (int)map.ceiling_color.y,
		(int)map.ceiling_color.z);
	ft_dprintf(fd, "FLOOR %d %d %d\n",
		(int)map.floor_color.x, (int)map.floor_color.y,
		(int)map.floor_color.z);
	ft_dprintf(fd, "NO_TEX %s\n", map.no_tex);
	ft_dprintf(fd, "EA_TEX %s\n", map.ea_tex);
	ft_dprintf(fd, "SO_TEX %s\n", map.so_tex);
	ft_dprintf(fd, "WE_TEX %s\n", map.we_tex);
	serialize_map_walls(fd, map);
	ft_dprintf(fd, "MAP_END\n");
}

static void	serialize_map_walls(int fd, t_map_info map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (map.map[i][j] == WALL)
				ft_dprintf(fd, "%d", 1);
			if (map.map[i][j] == EMPTY)
				ft_dprintf(fd, "%d", 0);
			if (map.map[i][j] == VOID)
				ft_dprintf(fd, " ");
			j++;
		}
		ft_dprintf(fd, "\n");
		i++;
	}
}
