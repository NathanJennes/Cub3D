/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialization_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 11:45:36 by njennes           #+#    #+#             */
/*   Updated: 2022/05/15 12:48:20 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

int			deserialize_map_parse_width(char *line, t_gamestate *save);
int			deserialize_map_parse_height(char *line, t_gamestate *save);
int			deserialize_map_parse_spawn(char *line, t_gamestate *save);
int			deserialize_map_parse_ceiling(char *line, t_gamestate *save);
int			deserialize_map_parse_floor(char *line, t_gamestate *save);
int			deserialize_map_parse_no_tex(char *line, t_gamestate *save);
int			deserialize_map_parse_ea_tex(char *line, t_gamestate *save);
int			deserialize_map_parse_so_tex(char *line, t_gamestate *save);
int			deserialize_map_parse_we_tex(char *line, t_gamestate *save);
int			deserialize_map_parse_map_content(char *line, t_gamestate *save);

static int	parse_line(char *line, t_gamestate *save);

int	deserialize_map(int fd, char *line, t_gamestate *save)
{
	gc_free(line);
	line = gc_get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "MAP_END", ft_strlen("MAP_END")) == 0)
		{
			gc_free(line);
			return (1);
		}
		if (!parse_line(line, save))
		{
			gc_free(line);
			return (0);
		}
		gc_free(line);
		line = gc_get_next_line(fd);
	}
	return (0);
}

static int	parse_line(char *line, t_gamestate *save)
{
	if (ft_strncmp(line, "W ", ft_strlen("W ")) == 0)
		return (deserialize_map_parse_width(line, save));
	if (ft_strncmp(line, "H ", ft_strlen("H ")) == 0)
		return (deserialize_map_parse_height(line, save));
	if (ft_strncmp(line, "SPAWN ", ft_strlen("SPAWN ")) == 0)
		return (deserialize_map_parse_spawn(line, save));
	if (ft_strncmp(line, "CEILING ", ft_strlen("CEILING ")) == 0)
		return (deserialize_map_parse_ceiling(line, save));
	if (ft_strncmp(line, "FLOOR ", ft_strlen("FLOOR ")) == 0)
		return (deserialize_map_parse_floor(line, save));
	if (ft_strncmp(line, "NO_TEX ", ft_strlen("NO_TEX ")) == 0)
		return (deserialize_map_parse_no_tex(line, save));
	if (ft_strncmp(line, "EA_TEX ", ft_strlen("EA_TEX ")) == 0)
		return (deserialize_map_parse_ea_tex(line, save));
	if (ft_strncmp(line, "SO_TEX ", ft_strlen("SO_TEX ")) == 0)
		return (deserialize_map_parse_so_tex(line, save));
	if (ft_strncmp(line, "WE_TEX ", ft_strlen("WE_TEX ")) == 0)
		return (deserialize_map_parse_we_tex(line, save));
	if (ft_isdigit(*line))
		return (deserialize_map_parse_map_content(line, save));
	return (0);
}
