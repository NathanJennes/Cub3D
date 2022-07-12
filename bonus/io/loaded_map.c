/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loaded_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:07:45 by njennes           #+#    #+#             */
/*   Updated: 2022/07/12 17:18:37 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <sys/stat.h>
#include "core.h"
#include "libft.h"

void		serialize_game(int fd);
int			deserialize_save(t_gamestate *save_out, int fd, char *filename);

inline static int	open_map_file(char *map_name, t_bool absolute);

int	load_map(t_gamestate *map_out, char *map_name, t_bool absolute)
{
	t_gamestate	save;
	int			fd;

	if (!map_name)
		return (0);
	ft_memset(&save, 0, sizeof (t_gamestate));
	fd = open_map_file(map_name, absolute);
	if (fd == -1)
		return (0);
	if (!deserialize_save(&save, fd, map_name))
	{
		gc_strarray_free(save.map.map_raw);
		if (save.map.map)
			gc_free2d((void **)save.map.map, save.map.height);
		return (0);
	}
	save.name = gc_strdup(map_name);
	close(fd);
	*map_out = save;
	return (1);
}

inline static int	open_map_file(char *map_name, t_bool absolute)
{
	int		fd;
	char	*map_file;

	if (!absolute)
	{
		map_file = gc_strdup(MAPS_DIRECTORY);
		map_file = gc_strappend(map_file, '/', LK_TRUE);
		map_file = gc_strjoin(map_file, map_name, FREE_FIRST);
	}
	else
		map_file = map_name;
	fd = open(map_file, O_RDWR, 0777);
	if (!absolute)
		gc_free(map_file);
	return (fd);
}
