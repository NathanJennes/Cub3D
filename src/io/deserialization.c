/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 11:05:43 by njennes           #+#    #+#             */
/*   Updated: 2022/05/15 11:29:18 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

int			deserialize_player(int fd, char *line, t_gamestate *save);
int			deserialize_map(int fd, char *line, t_gamestate *save);

static int	parse_line(int fd, char *line, t_gamestate *save);

t_gamestate	deserialize_save(int fd)
{
	t_gamestate	save;
	char		*line;

	ft_memset(&save, 0, sizeof (t_gamestate));
	line = gc_get_next_line(fd);
	while (line)
	{
		if (!parse_line(fd, line, &save))
		{
			cub_set_error(SAVE_ERROR);
			return (save);
		}
		line = gc_get_next_line(fd);
	}
}

static int	parse_line(int fd, char *line, t_gamestate *save)
{
	line = ft_trimr(line);
	if (ft_strncmp(line, "PLAYER_START", ft_strlen("PLAYER_START")) == 0)
		return (deserialize_player(fd, line, save));
	if (ft_strncmp(line, "MAP_START", ft_strlen("MAP_START")) == 0)
		return (deserialize_map(fd, line, save));
}
