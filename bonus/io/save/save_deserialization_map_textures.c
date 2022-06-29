/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization_map_textures.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:03:22 by njennes           #+#    #+#             */
/*   Updated: 2022/06/24 16:16:17 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

static char	*try_skip_str(char *line, char *str);

int	deserialize_map_parse_no_tex(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor = try_skip_str(cursor, "NO_TEX");
	cursor = ft_strskip_space(cursor);
	if (ft_strlen(cursor) == 0)
		return (0);
	else if (ft_strncmp(cursor, "(null)", ft_strlen(cursor)) == 0)
		save->map.tx_list[NORTH] = INVALID_TEXTURE;
	else
		save->map.tx_list[NORTH] = load_texture(cursor);
	return (1);
}

int	deserialize_map_parse_ea_tex(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor = try_skip_str(cursor, "EA_TEX");
	cursor = ft_strskip_space(cursor);
	if (ft_strlen(cursor) == 0)
		return (0);
	else if (ft_strncmp(cursor, "(null)", ft_strlen(cursor)) == 0)
		save->map.tx_list[EAST] = INVALID_TEXTURE;
	else
		save->map.tx_list[EAST] = load_texture(cursor);
	return (1);
}

int	deserialize_map_parse_so_tex(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor = try_skip_str(cursor, "SO_TEX");
	cursor = ft_strskip_space(cursor);
	if (ft_strlen(cursor) == 0)
		return (0);
	else if (ft_strncmp(cursor, "(null)", ft_strlen(cursor)) == 0)
		save->map.tx_list[SOUTH] = INVALID_TEXTURE;
	else
		save->map.tx_list[SOUTH] = load_texture(cursor);
	return (1);
}

int	deserialize_map_parse_we_tex(char *line, t_gamestate *save)
{
	char	*cursor;

	cursor = ft_trimr(line);
	cursor = try_skip_str(cursor, "WE_TEX");
	cursor = ft_strskip_space(cursor);
	if (ft_strlen(cursor) == 0)
		return (0);
	else if (ft_strncmp(cursor, "(null)", ft_strlen(cursor)) == 0)
		save->map.tx_list[WEST] = INVALID_TEXTURE;
	else
		save->map.tx_list[WEST] = load_texture(cursor);
	return (1);
}

static char	*try_skip_str(char *line, char *str)
{
	int64_t	i;

	i = 0;
	while (line[i] && str[i])
		i++;
	return (&line[i]);
}
