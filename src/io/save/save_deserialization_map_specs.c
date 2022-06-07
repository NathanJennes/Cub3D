/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deserialization_map_specs.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:03:22 by njennes           #+#    #+#             */
/*   Updated: 2022/05/15 12:43:02 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	deserialize_map_parse_width(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor = ft_strskip_alpha(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isdigit(*cursor))
		return (0);
	save->map.width = (size_t)ft_atoi(cursor);
	return (1);
}

int	deserialize_map_parse_height(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor = ft_strskip_alpha(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isdigit(*cursor))
		return (0);
	save->map.height = (size_t)ft_atoi(cursor);
	return (1);
}

int	deserialize_map_parse_spawn(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor = ft_strskip_alpha(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isdigit(*cursor) && *cursor != '-')
		return (0);
	save->map.spawn_pos.x = (float)ft_atoi(cursor);
	cursor = ft_strskip_digit(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isdigit(*cursor) && *cursor != '-')
		return (0);
	save->map.spawn_pos.y = (float)ft_atoi(cursor);
	cursor = ft_strskip_digit(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isalpha(*cursor))
		return (0);
	save->map.spawn_dir = *cursor;
	return (1);
}

int	deserialize_map_parse_ceiling(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor = ft_strskip_alpha(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isdigit(*cursor) && *cursor != '-')
		return (0);
	save->map.ceiling.r = (float)ft_atoi(cursor);
	cursor = ft_strskip_digit(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isdigit(*cursor) && *cursor != '-')
		return (0);
	save->map.ceiling.g = (float)ft_atoi(cursor);
	cursor = ft_strskip_digit(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isdigit(*cursor) && *cursor != '-')
		return (0);
	save->map.ceiling.b = (float)ft_atoi(cursor);
	return (1);
}

int	deserialize_map_parse_floor(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor = ft_strskip_alpha(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isdigit(*cursor) && *cursor != '-')
		return (0);
	save->map.floor.r = (float)ft_atoi(cursor);
	cursor = ft_strskip_digit(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isdigit(*cursor) && *cursor != '-')
		return (0);
	save->map.floor.b = (float)ft_atoi(cursor);
	cursor = ft_strskip_digit(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isdigit(*cursor) && *cursor != '-')
		return (0);
	save->map.floor.b = (float)ft_atoi(cursor);
	return (1);
}
