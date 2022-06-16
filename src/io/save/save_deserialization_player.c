/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization_player.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 11:27:47 by njennes           #+#    #+#             */
/*   Updated: 2022/05/25 17:53:41 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

inline static int	parse_line(char *line, t_gamestate *save);
inline static int	parse_pos(char *line, t_gamestate *save);

int	deserialize_player(int fd, char *line, t_gamestate *save)
{
	gc_free(line);
	line = gc_get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "PLAYER_END", ft_strlen("PLAYER_END")) == 0)
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

inline static int	parse_line(char *line, t_gamestate *save)
{
	if (ft_strncmp(line, "POS", ft_strlen("POS")) == 0)
		return (parse_pos(line, save));
	return (0);
}

inline static int	parse_pos(char *line, t_gamestate *save)
{
	char	*line_cursor;

	line_cursor = ft_trimr(line);
	line_cursor = ft_strchr(line_cursor, ' ');
	if (!line_cursor)
		return (0);
	line_cursor = ft_strskip_space(line_cursor);
	if (!ft_isdigit(*line_cursor) && *line_cursor != '-')
		return (0);
	save->player.world_pos.x = (float)ft_atoi(line_cursor);
	line_cursor = ft_strskip_digit(line_cursor);
	line_cursor = ft_strskip_space(line_cursor);
	if (!ft_isdigit(*line_cursor) && *line_cursor != '-')
		return (0);
	save->player.world_pos.y = (float)ft_atoi(line_cursor);
	line_cursor = ft_strskip_digit(line_cursor);
	line_cursor = ft_strskip_space(line_cursor);
	if (!ft_isdigit(*line_cursor) && *line_cursor != '-')
		return (0);
	save->player.direction = (float)ft_atoi(line_cursor);
	update_player(&save->player);
	return (1);
}
