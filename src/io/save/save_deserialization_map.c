/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization_map.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 11:45:36 by njennes           #+#    #+#             */
/*   Updated: 2022/06/17 16:22:07 by njennes          ###   ########.fr       */
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

inline static int	parse_line(char *line, t_gamestate *save, int64_t line_number);

int	deserialize_map(int fd, char *line, t_gamestate *save)
{
	int64_t	line_number;

	gc_free(line);
	line = gc_get_next_line(fd);
	line_number = 0;
	while (line)
	{
		if (ft_strncmp(line, "MAP_END", ft_strlen("MAP_END")) == 0)
		{
			gc_free(line);
			return (1);
		}
		if (!parse_line(line, save, line_number))
		{
			gc_free(line);
			return (0);
		}
		gc_free(line);
		line = gc_get_next_line(fd);
		line_number++;
	}
	return (0);
}

inline static int	parse_line(char *line, t_gamestate *save, int64_t line_number)
{
	if (line_number == 0)
		return (deserialize_map_parse_width(line, save));
	if (line_number == 1)
		return (deserialize_map_parse_height(line, save));
	if (line_number == 2)
		return (deserialize_map_parse_spawn(line, save));
	if (line_number == 3)
		return (deserialize_map_parse_ceiling(line, save));
	if (line_number == 4)
		return (deserialize_map_parse_floor(line, save));
	if (line_number == 5)
		return (deserialize_map_parse_no_tex(line, save));
	if (line_number == 6)
		return (deserialize_map_parse_ea_tex(line, save));
	if (line_number == 7)
		return (deserialize_map_parse_so_tex(line, save));
	if (line_number == 8)
		return (deserialize_map_parse_we_tex(line, save));
	if (ft_isdigit(*line) && line_number > 8)
		return (deserialize_map_parse_map_content(line, save));
	return (0);
}
