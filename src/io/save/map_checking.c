/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:50:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/27 15:14:06 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"
#include "core.h"
#include "map_error.h"

t_bool			is_spawn_char(char c, int64_t *has_spawn_out);
t_bool			is_inside(int64_t x_pos, char *line);
t_bool			check_edges(t_map_info *infos, t_map_parser *parser);
t_bool			check_edges_2(t_map_info *infos, t_map_parser *parser);
inline static t_bool	check_rows(t_map_info *infos, t_map_parser *parser);
inline static int		rows_error_type(t_map_info *infos, t_map_parser *parser,
					t_ivec2 pos, int64_t *spawn_count);

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
	int64_t	spawn_count;

	pos = ivec2(0, 0);
	spawn_count = 0;
	while (infos->map_raw[pos.y] && pos.y < infos->height)
	{
		pos.x = 0;
		while (infos->map_raw[pos.y][pos.x] && pos.x < infos->width)
		{
			if (!rows_error_type(infos, parser, pos, &spawn_count))
				return (0);
			pos.x++;
		}
		pos.y++;
	}
	if (spawn_count == 0)
		return (map_error_layout(infos, parser, MERR_MAP_NO_SPAWN,
				ivec2(-1, -1)));
	return (TRUE);
}

inline static int	rows_error_type(t_map_info *infos, t_map_parser *parser,
		t_ivec2 pos, int64_t *spawn_count)
{
	if (is_spawn_char(infos->map_raw[pos.y][pos.x], spawn_count))
	{
		if (*spawn_count > 1)
			return (map_error_layout(infos, parser,
					MERR_MAP_SPAWN_REDEFINITION, pos));
		if (!is_inside(pos.x, infos->map_raw[pos.y]))
			return (map_error_layout(infos, parser,
					MERR_MAP_INVALID_LINE_SIDES, pos));
	}
	else if (infos->map_raw[pos.y][pos.x] == '0')
	{
		if (!is_inside(pos.x, infos->map_raw[pos.y]))
			return (map_error_layout(infos, parser,
					MERR_MAP_INVALID_LINE_SIDES, pos));
	}
	else if (infos->map_raw[pos.y][pos.x] != ' '
		&& infos->map_raw[pos.y][pos.x] != '1')
		return (map_error_layout(infos, parser, MERR_MAP_WRONG_CHAR,
				pos));
	return (1);
}
