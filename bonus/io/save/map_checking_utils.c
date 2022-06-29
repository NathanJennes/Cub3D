/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cybattis <cybattis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:50:21 by njennes           #+#    #+#             */
/*   Updated: 2022/06/27 15:06:31 by cybattis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bool.h"
#include "core.h"
#include "map_error.h"

t_bool	is_spawn_char(char c, int64_t *has_spawn_out)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (has_spawn_out)
			(*has_spawn_out)++;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_inside(int64_t x_pos, char *line)
{
	int64_t	i;

	i = x_pos;
	while (i >= 0)
	{
		if (line[i] == '1')
			break ;
		else if (line[i] != '0' && !is_spawn_char(line[i], NULL))
			return (FALSE);
		i--;
	}
	if (i < 0 || line[i] != '1')
		return (FALSE);
	i = x_pos;
	while (line[i])
	{
		if (line[i] == '1')
			break ;
		else if (line[i] != '0' && !is_spawn_char(line[i], NULL))
			return (FALSE);
		i++;
	}
	if (line[i] != '1')
		return (FALSE);
	return (TRUE);
}

t_bool	check_edges_2(t_map_info *infos, t_map_parser *parser)
{
	t_ivec2	pos;

	pos = ivec2(0, 1);
	while (infos->map_raw[pos.y] && pos.y < infos->height - 1)
	{
		pos.x = 0;
		while (infos->map_raw[pos.y][pos.x] && pos.x < infos->width)
		{
			if (infos->map_raw[pos.y][pos.x] == '0'
				|| is_spawn_char(infos->map_raw[pos.y][pos.x], NULL))
			{
				if ((int64_t)ft_strlen(infos->map_raw[pos.y - 1]) - 1 < pos.x
					|| infos->map_raw[pos.y - 1][pos.x] == ' ')
					return (map_error_layout(infos, parser, MERR_MAP_HOLE_NORTH,
							pos));
				if ((int64_t)ft_strlen(infos->map_raw[pos.y + 1]) - 1 < pos.x
					|| infos->map_raw[pos.y + 1][pos.x] == ' ')
					return (map_error_layout(infos, parser, MERR_MAP_HOLE_SOUTH,
							pos));
			}
			pos.x++;
		}
		pos.y++;
	}
	return (TRUE);
}

t_bool	check_edges(t_map_info *infos, t_map_parser *parser)
{
	int64_t	i;

	i = 0;
	while (infos->map_raw[0][i] && i < infos->width)
	{
		if (infos->map_raw[0][i] == '0'
			|| is_spawn_char(infos->map_raw[0][i], NULL))
			return (map_error_layout(infos, parser, MERR_MAP_EDGE_NOT_WALL,
					ivec2(i, 0)));
		i++;
	}
	if (!check_edges_2(infos, parser))
		return (FALSE);
	i = 0;
	while (infos->map_raw[infos->height - 1][i] && i < infos->width)
	{
		if (infos->map_raw[infos->height - 1][i] == '0'
			|| is_spawn_char(infos->map_raw[infos->height - 1][i], NULL))
			return (map_error_layout(infos, parser, MERR_MAP_EDGE_NOT_WALL,
					ivec2(i, infos->height - 1)));
		i++;
	}
	return (TRUE);
}
