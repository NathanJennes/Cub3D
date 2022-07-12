/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 11:05:43 by njennes           #+#    #+#             */
/*   Updated: 2022/06/24 16:06:16 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"

int			deserialize_player(int fd, char *line, t_gamestate *save);
int			deserialize_map(int fd, char *line, t_gamestate *save);
void		construct_map(t_map_info *infos);
int			load_mandatory_map(t_gamestate *save_out, int fd, char *line,
				char *filename);

inline static int	parse_line_save(int fd, char *line, t_gamestate *save);
inline static int	deserialize_cub_save(t_gamestate *save_out, int fd);

int	deserialize_save(t_gamestate *save_out, int fd, char *filename)
{
	char	*line;

	line = gc_get_next_line(fd);
	if (!line)
		return (0);
	line = ft_trimr(line);
	if (ft_strcmp(line, "CUB_SAVE") == 0)
		return (deserialize_cub_save(save_out, fd));
	return (load_mandatory_map(save_out, fd, line, filename));
}

inline static int	deserialize_cub_save(t_gamestate *save_out, int fd)
{
	t_gamestate	save;
	char		*line;

	ft_memset(&save, 0, sizeof (t_gamestate));
	line = gc_get_next_line(fd);
	while (line)
	{
		if (!parse_line_save(fd, line, &save))
		{
			gc_strarray_free(save.map.map_raw);
			return (0);
		}
		line = gc_get_next_line(fd);
	}
	construct_map(&save.map);
	gc_strarray_free(save.map.map_raw);
	if (!save.map.spawn_dir)
		return (0);
	if (!is_player_position_legal(&save))
		return (0);
	*save_out = save;
	return (1);
}

inline static int	parse_line_save(int fd, char *line, t_gamestate *save)
{
	line = ft_trimr(line);
	if (ft_strncmp(line, "PLAYER_START", ft_strlen("PLAYER_START")) == 0)
		return (deserialize_player(fd, line, save));
	if (ft_strncmp(line, "MAP_START", ft_strlen("MAP_START")) == 0)
		return (deserialize_map(fd, line, save));
	return (0);
}