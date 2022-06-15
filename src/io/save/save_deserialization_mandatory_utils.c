/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization_mandatory_utils.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:45:01 by njennes           #+#    #+#             */
/*   Updated: 2022/06/07 17:15:37 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "core.h"
#include "leaky.h"

inline static int	contains_illegal_char(t_map_info *infos, char *line)NOPROF;
inline static int	is_illegal_char(char c, t_map_info *infos, int *saw_wall,
		int *last_is_wall)NOPROF;

int	parse_color(t_rgb *color, char *line)
{
	if (!ft_isdigit(*line))
		return (0);
	color->r = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line != ',')
		return (0);
	line++;
	color->g = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line != ',')
		return (0);
	line++;
	color->b = ft_atoi(line);
	return (1);
}

int	parse_texture(t_map_info *info, char *line)
{
	int64_t	*temp;

	if (!*line)
		return (0);
	if (!info->tx_list)
		info->tx_list = gc_alloc(sizeof(int64_t));
	else
	{
		temp = gc_alloc(sizeof(int64_t) * (info->tx_count + 1));
		gc_memmove(temp, info->tx_list, info->tx_count * sizeof(int64_t));
		gc_free(info->tx_list);
		info->tx_list = temp;
	}
	info->tx_list[info->tx_count] = load_texture(line);
	if (info->tx_list[info->tx_count] == INVALID_TEXTURE)
		return (0);
	info->tx_count++;
	return (1);
}

int	add_map_row(t_map_info *infos, char *line)
{
	infos->height++;
	line = ft_trimr(line);
	if (contains_illegal_char(infos, line))
		return (0);
	if (!infos->map_raw)
		infos->map_raw = gc_strarray_init();
	infos->map_raw = gc_strarray_append(infos->map_raw, line);
	line = ft_trimr(line);
	if ((int64_t)ft_strlen(line) > infos->width)
		infos->width = ft_strlen(line);
	return (1);
}

inline static int	contains_illegal_char(t_map_info *infos, char *line)
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

inline static int	is_illegal_char(char c, t_map_info *infos, int *saw_wall,
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
