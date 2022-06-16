/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:50:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/16 19:12:20 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"
#include "core.h"
#include "map_error.h"

inline static t_bool	check_rows(t_map_info *infos, t_map_parser *parser);
inline static t_bool	check_edges(t_map_info *infos, t_map_parser *parser);
inline static t_bool	check_edges_2(t_map_info *infos, t_map_parser *parser);
inline static t_bool	is_spawn_char(char c, t_bool *has_spawn_out);

t_bool	is_legal_map(t_map_info *infos, t_map_parser *parser)
{
	if (!infos->map_raw)
		return (map_error(NULL, parser, MERR_MAP_EMPTY));
	if (infos->width <= 2 || infos->height <= 2)
		return (map_error_layout(NULL, parser, MERR_MAP_SIZE, ivec2_zero()));
	if (!check_rows(infos, parser))
		return (FALSE);
	if (!check_edges(infos, parser))
		return (FALSE);
	return (TRUE);
}

inline static t_bool	check_rows(t_map_info *infos, t_map_parser *parser)
{
	t_ivec2	pos;
	int64_t	is_inside;
	t_bool	last_was_wall;
	t_bool	has_spawn;

	pos = ivec2(0, 0);
	while (infos->map_raw[pos.y] && pos.y < infos->height)
	{
		pos.x = 0;
		is_inside = 0;
		last_was_wall = FALSE;
		while (infos->map_raw[pos.y][pos.x] && pos.x < infos->width)
		{
			if (has_spawn && is_spawn_char(infos->map_raw[pos.y][pos.x], &has_spawn))
				return (map_error_layout(infos, parser, MERR_MAP_SPAWN_REDEFINITION, pos));
			else if (infos->map_raw[pos.y][pos.x] == '0' && !is_inside)
				return (map_error_layout(infos, parser, MERR_MAP_INVALID_LINE_SIDES, pos));
			else if (infos->map_raw[pos.y][pos.x] == '1')
			{
				is_inside = TRUE;
				if (!last_was_wall)
					is_inside = FALSE;
				last_was_wall = TRUE;
			}
			else if (infos->map_raw[pos.y][pos.x] != ' ')
				return (map_error_layout(infos, parser, MERR_MAP_WRONG_CHAR, pos));
			pos.x++;
		}
		pos.y++;
	}
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
	return (check_edges(infos, parser));
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
	i = 0;
	while (infos->map_raw[1][i] && i < infos->width)
	{
		if (infos->map_raw[1][i] == '0')
			return (map_error_layout(infos, parser, MERR_MAP_EDGE_NOT_WALL, ivec2(i, 1)));
		i++;
	}
	return (TRUE);
}

inline static t_bool	is_spawn_char(char c, t_bool *has_spawn_out)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		*has_spawn_out = TRUE;
		return (TRUE);
	}
	return (FALSE);
}
