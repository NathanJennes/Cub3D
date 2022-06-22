/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization_map_specs.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:03:22 by njennes           #+#    #+#             */
/*   Updated: 2022/06/17 16:15:56 by njennes          ###   ########.fr       */
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
	save->map.width = ft_atoi(cursor);
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
	save->map.height = ft_atoi(cursor);
	return (1);
}

//TODO: check if spawn is in map
int	deserialize_map_parse_spawn(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor = ft_strskip_alpha(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isdigit(*cursor))
		return (0);
	save->map.spawn_pos.x = ft_atoi(cursor);
	cursor = ft_strskip_digit(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isdigit(*cursor))
		return (0);
	save->map.spawn_pos.y = ft_atoi(cursor);
	cursor = ft_strskip_digit(cursor);
	cursor = ft_strskip_space(cursor);
	if (!ft_isalpha(*cursor))
		return (0);
	save->map.spawn_dir = *cursor;
	return (1);
}

int	deserialize_map_parse_ceiling(char *line, t_gamestate *save)
{
	int		color;
	char	*cursor;

	cursor = ft_trimr(line);
	cursor = ft_strskip_space(ft_strskip_alpha(cursor));
	if (!ft_isdigit(*cursor))
		return (0);
	color = ft_atoi(cursor);
	if (color < 0 || color > 255)
		return (0);
	save->map.ceiling.r = color;
	cursor = ft_strskip_space(ft_strskip_digit(cursor));
	if (!ft_isdigit(*cursor))
		return (0);
	color = ft_atoi(cursor);
	if (color < 0 || color > 255)
		return (0);
	save->map.ceiling.g = color;
	cursor = ft_strskip_space(ft_strskip_digit(cursor));
	if (!ft_isdigit(*cursor))
		return (0);
	color = ft_atoi(cursor);
	if (color < 0 || color > 255)
		return (0);
	save->map.ceiling.b = color;
	return (1);
}

int	deserialize_map_parse_floor(char *line, t_gamestate *save)
{
	int		color;
	char	*cursor;

	cursor = ft_trimr(line);
	cursor = ft_strskip_space(ft_strskip_alpha(cursor));
	if (!ft_isdigit(*cursor))
		return (0);
	color = ft_atoi(cursor);
	if (color < 0 || color > 255)
		return (0);
	save->map.floor.r = color;
	cursor = ft_strskip_space(ft_strskip_digit(cursor));
	if (!ft_isdigit(*cursor))
		return (0);
	color = ft_atoi(cursor);
	if (color < 0 || color > 255)
		return (0);
	save->map.floor.g = color;
	cursor = ft_strskip_space(ft_strskip_digit(cursor));
	if (!ft_isdigit(*cursor))
		return (0);
	color = ft_atoi(cursor);
	if (color < 0 || color > 255)
		return (0);
	save->map.floor.b = color;
	return (1);
}
