/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialization_settings.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:30:37 by cybattis          #+#    #+#             */
/*   Updated: 2022/05/20 14:32:56 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"
#include "io.h"

static int	parse_line(char *line, t_gamestate *save);
static int	parse_fov(char *line, t_gamestate *save);

int	deserialize_settings(int fd, char *line, t_gamestate *save)
{
	gc_free(line);
	line = gc_get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "SETTINGS_END", ft_strlen("SETTINGS_END")) == 0)
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
	if (ft_strncmp(line, "FOV", ft_strlen("FOV")) == 0)
		return (parse_fov(line, save));
	return (0);
}

static int	parse_fov(char *line, t_gamestate *save)
{
	char	*line_cursor;

	line_cursor = ft_trimr(line);
	line_cursor = ft_strchr(line_cursor, ' ');
	if (!line_cursor)
		return (0);
	line_cursor = ft_strskip_space(line_cursor);
	if (!ft_isdigit(*line_cursor) && *line_cursor != '-')
		return (0);
	save->settings.fov = ft_atoi(line_cursor);
	return (1);
}
