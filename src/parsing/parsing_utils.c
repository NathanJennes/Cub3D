/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:45:01 by njennes           #+#    #+#             */
/*   Updated: 2022/05/14 20:02:00 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "parsing.h"
#include "core.h"
#include "leaky.h"

static int	contains_illegal_char(t_map_info *infos, char *line);
static int	is_illegal_char(char c, t_map_info *infos, int *saw_wall,
				int *last_is_wall);

t_vec3	parse_color(char *line)
{
	t_vec3	color;

	if (!ft_isdigit(*line))
		error_close_app();
	color.x = ft_atoi(line);
	if (color.x < 0 || color.x > 255)
		error_close_app();
	while (ft_isdigit(*line))
		line++;
	if (*line != ',')
		error_close_app();
	line++;
	color.y = ft_atoi(line);
	if (color.y < 0 || color.y > 255)
		error_close_app();
	while (ft_isdigit(*line))
		line++;
	if (*line != ',')
		error_close_app();
	line++;
	color.z = ft_atoi(line);
	if (color.z < 0 || color.z > 255)
		error_close_app();
	return (color);
}

char	*parse_texture(char *line)
{
	char	*path;
	int		fd;

	if (!*line)
		error_close_app();
	path = gc_strdup(line);
	fd = open(path, O_RDONLY);
	if (!fd || fd == -1)
		error_close_app();
	close(fd);
	return (path);
}

void	add_map_row(t_map_info *infos, char *line)
{
	infos->height++;
	line = ft_trimr(line);
	if (contains_illegal_char(infos, line))
		error_close_app();
	if (!infos->map_raw)
		infos->map_raw = gc_strarray_init();
	infos->map_raw = gc_strarray_append(infos->map_raw, line);
	line = ft_trimr(line);
	if (ft_strlen(line) > infos->width)
		infos->width = ft_strlen(line);
}

static int	contains_illegal_char(t_map_info *infos, char *line)
{
	size_t	i;
	int		saw_wall;
	int		last_is_wall;

	i = 0;
	saw_wall = 0;
	last_is_wall = 0;
	while (line[i])
	{
		if (is_illegal_char(line[i], infos, &saw_wall, &last_is_wall))
			return (1);
		i++;
	}
	if (!saw_wall || !last_is_wall)
		return (1);
	return (0);
}

static int	is_illegal_char(char c, t_map_info *infos, int *saw_wall,
				int *last_is_wall)
{
	if (c == '1')
	{
		*saw_wall = 1;
		*last_is_wall = 1;
	}
	else if (ft_isalpha(c) && (!(c == 'W' || c == 'S'
				|| c == 'N' || c == 'E') || !saw_wall
			|| infos->spawn_dir))
		return (1);
	else if (c != '0' && !ft_isalpha(c) && c != ' ')
		return (1);
	else
		*last_is_wall = 0;
	return (0);
}
