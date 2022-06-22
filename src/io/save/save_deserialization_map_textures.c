/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_deserialization_map_textures.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:03:22 by njennes           #+#    #+#             */
/*   Updated: 2022/06/17 15:39:12 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

int	deserialize_map_parse_no_tex(char *line, t_gamestate *save)
{
	char	*cursor;

	(void)save;
	cursor = ft_trimr(line);
	//TODO: this can segfault
	cursor += ft_strlen("NO_TEX");
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

	(void)save;
	cursor = ft_trimr(line);
	//TODO: this can segfault
	cursor += ft_strlen("EA_TEX");
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

	(void)save;
	cursor = ft_trimr(line);
	//TODO: this can segfault
	cursor += ft_strlen("SO_TEX");
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

	(void)save;
	cursor = ft_trimr(line);
	//TODO: this can segfault
	cursor += ft_strlen("WE_TEX");
	cursor = ft_strskip_space(cursor);
	if (ft_strlen(cursor) == 0)
		return (0);
	else if (ft_strncmp(cursor, "(null)", ft_strlen(cursor)) == 0)
		save->map.tx_list[WEST] = INVALID_TEXTURE;
	else
		save->map.tx_list[WEST] = load_texture(cursor);
	return (1);
}
