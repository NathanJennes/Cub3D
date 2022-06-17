/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:50:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/16 20:50:11 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"
#include "core.h"
#include "map_error.h"

inline static t_bool	check_rows(t_map_info *infos, t_map_parser *parser);
inline static t_bool	check_edges(t_map_info *infos, t_map_parser *parser);
inline static t_bool	check_edges_2(t_map_info *infos, t_map_parser *parser);
inline static t_bool	is_spawn_char(char c, int64_t *has_spawn_out);

t_bool	is_map_legal(t_map_info *infos, t_map_parser *parser)
{
	if (!infos->map_raw)
		return (map_error(NULL, parser, MERR_MAP_EMPTY));
	if (infos->width <= 2 || infos->height <= 2)
		return (map_error_layout(infos, parser, MERR_MAP_SIZE, ivec2(-1, -1)));
	if (!check_rows(infos, parser))
		return (FALSE);
	if (!check_edges(infos, parser))
		return (FALSE);
	return (TRUE);
}

inline static t_bool	check_rows(t_map_info *infos, t_map_parser *parser)
{
	t_ivec2	pos;
	t_bool	is_inside;
	int64_t	spawn_count;

	pos = ivec2(0, 0);
	spawn_count = 0;
	while (infos->map_raw[pos.y] && pos.y < infos->height)
	{
		pos.x = 0;
		is_inside = FALSE;
		while (infos->map_raw[pos.y][pos.x] && pos.x < infos->width)
		{
			if (is_spawn_char(infos->map_raw[pos.y][pos.x], &spawn_count))
			{
				if (spawn_count > 1)
					return (map_error_layout(infos, parser, MERR_MAP_SPAWN_REDEFINITION, pos));
			}
			else if (infos->map_raw[pos.y][pos.x] == '0')
			{
				if (!is_inside)
					return (map_error_layout(infos, parser, MERR_MAP_INVALID_LINE_SIDES, pos));
			}
			else if (infos->map_raw[pos.y][pos.x] == '1')
				is_inside = TRUE;
			else if (infos->map_raw[pos.y][pos.x] == ' ')
				is_inside = FALSE;
			else
				return (map_error_layout(infos, parser, MERR_MAP_WRONG_CHAR, pos));
			pos.x++;
		}
		pos.y++;
	}
	if (spawn_count == 0)
		return (map_error_layout(infos, parser, MERR_MAP_NO_SPAWN, ivec2(-1, -1)));
	return (TRUE);
}

inline static t_bool	check_edges_2(t_map_info *infos, t_map_parser *parser)
{
	t_ivec2	pos;

	pos = ivec2(0, 1);
	while (infos->map_raw[pos.y] && pos.y < infos->height - 1)
	{
		pos.x = 0;
		while (infos->map_raw[pos.y][pos.x] && pos.x < infos->width)
		{
			if (infos->map_raw[pos.y][pos.x] == '0')
			{
				if ((int64_t)ft_strlen(infos->map_raw[pos.y - 1]) - 1 < pos.x || infos->map_raw[pos.y - 1][pos.x] == ' ')
					return (map_error_layout(infos, parser, MERR_MAP_HOLE_NORTH, pos));
				if ((int64_t)ft_strlen(infos->map_raw[pos.y + 1]) - 1 < pos.x || infos->map_raw[pos.y + 1][pos.x] == ' ')
					return (map_error_layout(infos, parser, MERR_MAP_HOLE_SOUTH, pos));
			}
			pos.x++;
		}
		pos.y++;
	}
	return (TRUE);
}

inline static t_bool	check_edges(t_map_info *infos, t_map_parser *parser)
{
	int64_t	i;

	i = 0;
	while (infos->map_raw[0][i] && i < infos->width)
	{
		if (infos->map_raw[0][i] == '0')
			return (map_error_layout(infos, parser, MERR_MAP_EDGE_NOT_WALL, ivec2(i, 0)));
		i++;
	}
	if (!check_edges_2(infos, parser))
		return (FALSE);
	i = 0;
	while (infos->map_raw[infos->height - 1][i] && i < infos->width)
	{
		if (infos->map_raw[infos->height - 1][i] == '0')
			return (map_error_layout(infos, parser, MERR_MAP_EDGE_NOT_WALL, ivec2(i, infos->height - 1)));
		i++;
	}
	return (TRUE);
}

inline static t_bool	is_spawn_char(char c, int64_t *has_spawn_out)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*has_spawn_out)++;
		return (TRUE);
	}
	return (FALSE);
}
