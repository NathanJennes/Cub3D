/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loaded_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:07:45 by njennes           #+#    #+#             */
/*   Updated: 2022/06/29 17:05:12 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <sys/stat.h>
#include "core.h"

int			deserialize_save(t_gamestate *save_out, int fd, char *filename);

int	load_map(t_gamestate *map_out, char *map_name)
{
	t_gamestate	save;
	int			fd;

	if (!map_name)
		return (0);
	ft_memset(&save, 0, sizeof (t_gamestate));
	fd = open(map_name, O_RDONLY);
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
